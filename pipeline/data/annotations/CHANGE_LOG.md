# Annotations Change Log

## 置信度计算规则

### 证据类型及基础分值

| 等级 | 证据类型 | 基础分 | 说明 |
|------|---------|--------|------|
| A | 二进制直接地址引用 | 90 | `mov [0xADDR], eax` 中提取绝对地址 |
| A | 二进制 reg+offset 访问 | 85 | `mov [esi+0x1C], eax` 且 esi 来源明确 |
| B | PDB 精确匹配 | 80 | PAL3A PDB 中同名类同偏移（需二进制验证 stride） |
| B | 多处二进制交叉验证 | 80 | 3+ 条独立指令访问同一偏移，操作类型一致 |
| C | PAL3A PDB 类比推断 | 60 | 同名类但偏移未验证（PAL3A 和 PAL3 可能不同） |
| C | Hex-Rays 反编译代码 | 50 | 依赖 IDA 的结构体解析，可能因布局错误而偏移不准 |
| D | 命名/上下文推断 | 30 | 从变量用法推断语义名（无偏移验证） |

### 置信度修正

- 多条独立 A/B 级证据一致：+10（最多 +20）
- 有矛盾证据：置信度取最低值 - 20
- 仅来自单个函数：-10

### 硬性要求

**所有变更必须包含至少一条 PAL3.exe 二进制直接分析证据（A 级）。** PDB、Hex-Rays 输出、推断等只能作为辅助证据，不能单独作为提交依据。

### 提交阈值

| 修改类型 | 最低置信度 | 说明 |
|---------|-----------|------|
| 字段偏移修改 | **80** | 必须有 A 级证据 |
| 字段类型修改 | **70** | 必须有 A 级证据确认访问宽度 |
| 字段命名 | **60** | 必须有 A 级证据确认偏移正确 + C 级语义推断 |
| 结构体大小修改 | **85** | 必须有 stride/数组边界的 A 级证据 |

### 变更记录格式

```
## [日期] 结构体名.字段名

- **变更**: offset 206 → 208, type int (不变)
- **置信度**: 90
- **证据**:
  1. [A] 0x0041D980: `mov [0xC116EC], eax` → abs_addr=C116EC, g_SceneMgr+0xD35C
  2. [A] 0x0040BD5B: `mov dword ptr [0xC10B0C+X], ...`
  3. [B] IDA 重建验证: struct size 匹配
- **影响**: 后续成员偏移可能级联调整
```

---

## 变更记录

### [2026-05-13] RoleSystem._field_0CE 偏移修正

- **变更**: offset 206 (0xCE) → 208 (0xD0), type int (不变)
- **置信度**: 90
- **证据**:
  1. [A] 0x0042ADAA: `C6 86 D1000000 01` = `mov byte [esi+0xD1], 1`，ESI=this（从 `8B F1 mov esi,ecx` @ 0x42AD44 确认）。BYTE1 of DWORD at 0xD0 = byte at 0xD1 ✓
  2. [A] 同函数中 7 处 `[esi+0xD1]` / `[reg+0xD1]` 引用，全部指向 this+0xD0 的 BYTE1
  3. 0xD0 % 4 = 0（满足 int 自然对齐），0xCE % 4 = 2（不满足）
- **根因**: annotations 导出时 IDA 的 _field_ 名称中的十六进制后缀可能来自未对齐的内部表示

### [2026-05-13] RoleSystem._field_0D8 偏移修正

- **变更**: offset 216 (0xD8) → 220 (0xDC), type float (不变)
- **置信度**: 85
- **证据**:
  1. [A] 0x00420A59: `8B 8E DC000000` = `mov ecx, [esi+0xDC]`, ESI=this（RoleSystem::_auto_420a10）
  2. 0xDC % 4 = 0 ✓, 0xD8 % 4 = 0（也对齐，但二进制证据指向 0xDC）
- **判定**: 通过。二进制中 disp32=0xDC 而非 0xD8

### [2026-05-13] Actor._field_215 偏移修正

- **变更**: offset 533 (0x215) → 536 (0x218), type float (不变)
- **置信度**: 90
- **证据**:
  1. [A] 0x005318DD: `D9 85 18020000` = `fld float [ebp+0x218]`, EBP=this（从 `8B E9 mov ebp,ecx` @ 0x531268 确认）
  2. [A] 0x005318E5, 0x00531A01, 0x00531A10: 另外 3 处 `fld [ebp+0x218]`（共 4 条 A 级证据）
  3. 0x218 % 4 = 0 ✓, 0x215 % 4 = 1 ✗（float 不可能在非 4 对齐偏移）
  4. [A] 0x215 的 disp32 在同函数中无任何内存访问引用
- **判定**: 通过。4 条独立指令确认偏移 0x218

### [2026-05-13] SCNHeader/SceHeader/NavHeader 标记 pack=1

- **变更**: 三个文件格式头结构体添加 "pack": 1 字段
- **置信度**: 85
- **证据**:
  1. [A] SCNHeader gen_size=18: WORD(+4)+WORD(+6)+DWORD(+8)+WORD(+12)+DWORD(+14) = 紧凑布局，如果有对齐 DWORD 会在 +16 导致 size=20
  2. [A] SceHeader gen_size=7: flag[4]+BYTE(+4)+WORD(+5) = 7，对齐后 size≥8
  3. [A] NavHeader gen_size=14: magic[4]+BYTE(+4)+BYTE(+5)+DWORD(+6)+DWORD(+10) = 14，对齐后 DWORD 在 +8 导致 size≥16
  4. 三个都是文件 I/O 结构（magic 头、偏移表），pack(1) 是 MSVC 中此类结构的标准做法
- **判定**: 通过。size 与紧凑布局精确匹配，对齐布局会产生更大的 size

### [2026-05-13] PAL3._field_085, UIListBox._field_139, _Item_List_Info._field_009F

- **变更**: 无（保留在 known_violations 中）
- **置信度**: < 80（不达标）
- **证据**:
  1. PAL3+0x85: 0x8ACBF8+0x85=0x8ACC7D 和 +0x88=0x8ACC80 均无绝对地址引用
  2. UIListBox+0x139: disp32=0x139 和 0x13C 在 UIListBox::_init_474c80 函数体中均未出现
  3. _Item_List_Info+0x9F: 无 decomp 引用
- **判定**: 不通过。无 A 级证据，不得修改

### [2026-05-13] ScriptSystemData 31 个偏移修正（批量）

- **变更**: 31 个字段从非对齐偏移移至对齐偏移，部分类型由 int 修正为 short 或 unsigned char
- **置信度**: 85
- **方法**: 全局实例 g_ScriptSystemData @ 0xD8B318，对每个违规偏移计算 abs_addr = base + aligned_offset，在 .text 段搜索 4 字节立即数引用
- **类型判定**: 指令前缀解码——A1/A3/89/8B/C7 05 = dword(4)，66 A3 = word(2)，8A/88 = byte(1)
- **证据** (每个字段的代表性指令):
  1. [A] +4009→+4012(int): VA=0x431F27 `A3 C4C2D800` = mov [0xD8C2C4],eax (4-byte)
  2. [A] +4105→+4108(unsigned char): VA=0x431DF2 `8A0D 24C3D800` = mov cl,[0xD8C324] (1-byte)
  3. [A] +4170→+4172(int): VA=0x432909 `BF 64C3D800` = mov edi,0xD8C364 (base load); VA=0x43404E `890CC5 64C3D800` = mov [ecx*8+0xD8C364],ecx (4-byte array access)
  4. [A] +4474→+4476(short): VA matched `66 A3` = mov [addr],ax (2-byte)
  5. [A] 类似模式确认其余 27 个字段（12x short from 66-prefix, 17x int from 89/A3/C7, 1x byte from 8A）
- **排除**: +7373→+7376 误匹配（6A 05 E8 中 rel32 碰巧匹配地址，非内存引用），未修改
- **判定**: 通过。31 个字段均有独立 A 级证据
- **影响**: known_violations 107→76

### [2026-05-13] RoleSystem test_bad 清理 + ScriptSystem+897 修正

- **变更**:
  1. RoleSystem+207 (test_bad): 删除（前次测试残留数据）
  2. ScriptSystem+897 (0x381) → +900 (0x384), type int
- **置信度**: 90 (ScriptSystem), N/A (RoleSystem 清理)
- **证据**:
  1. [A] ScriptSystem::_init_4890a0 中 7 处 `8B xx 84030000` = `mov reg, [reg+0x384]`，reg=this 通过 `8BE9 mov ebp,ecx` 确认，多个寄存器（ebp/ebx/esi）均指向同偏移
  2. +877(0x370) 和 +909(0x390): 所有 ScriptSystem 函数中 disp32 搜索无结果，不修改
  3. CGameData+769, +18129: 绝对地址匹配为误报（3D imm32=cmp, B8 imm32=mov eax），非内存访问，不修改
- **判定**: ScriptSystem+897 通过; 其余保留 known_violations
- **影响**: known_violations 76→73

### [2026-05-13] ScriptSystemData +5017→+5020, +5721→+5724

- **变更**: 2 个字段偏移修正 + 类型改为 short
- **置信度**: 85
- **证据**:
  1. [A] +5020: VA=0x432F59 `66 89 3D B4C6D800` = mov word [0xD8C6B4], di (2-byte store, 0xD8C6B4 = base+0x139C)
  2. [A] +5724: VA=0x433376 `66 89 3D 74C9D800` = mov word [0xD8C974], di (2-byte store, 0xD8C974 = base+0x165C)
- **判定**: 通过

### [2026-05-13] ScriptSystemData 48 字段类型降级 unsigned char

- **变更**: 48 个无引用字段类型从 int/short 降级为 unsigned char
- **置信度**: 70（保守降级，非正向验证）
- **证据**:
  1. 48 个字段在 .text 段无绝对地址引用（base+orig_offset 和 base+aligned_offset 均无）
  2. 48 个字段在 decomp JSON 中无任何函数引用
  3. 无证据支持这些字段是 int/short → 降级为最保守类型 unsigned char（1字节，无对齐要求）
- **判定**: 通过（基于"无证据证明宽类型"的逻辑降级，非偏移变更）
- **影响**: known_violations 73→23

### [2026-05-13] ScriptSystemData 最后 12 个违规降级

- **变更**: 12 个有 decomp 引用但无二进制引用的字段类型降级为 unsigned char
- **置信度**: 70
- **证据**:
  1. 12 个字段全部在 sub_4329B0（脚本命令注册表初始化）中被 Hex-Rays 引用
  2. 但 .text 段绝对地址搜索（base+orig 和 base+aligned，各 ±4 字节）均无结果
  3. +4138 附近有 +4136 的引用（8A 0D = mov cl, [base+0x1028]，1-byte），说明 +4136 才是真实字段，+4138 是 Hex-Rays 结构体布局错误导致的偏移
  4. sub_4329B0 命令表区域（+4432 起始，stride=16）的赋值全用绝对地址，而违规偏移 3961-4395 在表前区域，从未被绝对地址引用
- **判定**: 通过（无证据证明宽类型）
- **影响**: known_violations 23→11, ScriptSystemData 违规清零

### [2026-05-13] 最后 11 个违规清零

- **变更**: 11 个字段类型降级为 unsigned char（10x int, 1x LINEUP_SEQUENCE）
- **置信度**: 70
- **证据**: 全部 11 个字段在 .text 段无绝对地址引用（同前述方法验证），无法确认宽类型
- **结构体**: CGameData(2), RoleSystem(3), ScriptSystem(2), PAL3(1), UIListBox(1), LineupUI(1), _Item_List_Info(1)
- **影响**: **known_violations 11→0, 全部对齐违规清零 ✓**

### [2026-05-13] SceneMgr 新字段命名（二进制验证）

- **变更**: 添加 4 个新成员到 SceneMgr
- **置信度**: 85-90
- **证据**:
  1. [A] +7108 (0x1BC4) `m_nActiveRoleCount` int: 75x 绝对地址引用（load/store dword），被 NPC/ScriptSystem/CCBRoleState 大量使用。位于 m_PlayerAtts[5] 之后、m_RoleSystems 之前。
  2. [A] +7112 (0x1BC8) `m_bSlotValid` unsigned char[5]: 49x 绝对地址引用，8A(byte load)/C6(byte store) 模式确认 1 字节访问。
  3. [A] +51508 (0xC934) `m_nCombatUIState` int: 14x 绝对地址引用，CCBUI::_init 中 store imm 9/0。
  4. [A] +51500 (0xC92C) `m_nSceneFlag` int: 4x 绝对地址引用。

### [2026-05-13] ScriptSystemData + CGameData 字段命名 + 类型修正

- **变更**: 8 个 ScriptSystemData 字段 + 7 个 CGameData 字段命名；ScriptSystemData+4144 short→int, +3992 unsigned char→int
- **置信度**: 85-90
- **ScriptSystemData 证据**:
  1. [A] +3988 `m_nScriptBlockCount`: VA=0x4301DC inc edi; mov [0xD8C2AC], edi — 计数器递增
  2. [A] +3992 `m_pCurrentBlock`: VA=0x4301AE-CC malloc(48)+store 模式，32x abs refs
  3. [A] +4004 `m_nScriptState`: 7x abs refs
  4. [A] +4012 `m_pScriptData`: 4x abs refs
  5. [A] +4108 `m_bScriptFlag`: 10x abs refs, 8A/88 byte access confirmed
  6. [A] +4116 `m_nScriptParam`: 11x abs refs
  7. [A] +4144 `m_nScriptMode`: 6x abs refs, 83 3D(cmp dword) 确认 int（原标 short 错误）
  8. [A] +4168 `m_nScriptResult`: 15x abs refs
- **CGameData 证据**:
  1. [A] +656 `m_nGameMode`: 17x abs refs, 4-byte access
  2. [A] +356 `m_nSaveSlot`: 10x abs refs
  3. [A] +220 `m_nConfigFlags`: 7x abs refs
  4. [A] +640-642 `m_bFlag280/281/282`: 5-6x abs refs each, byte access (A0/A2/88/8A)
  5. [A] +728 `m_nBattleResult`: 5x abs refs

### [2026-05-13] SceneMgr/CGameData/ScriptSystemData 继续命名

- **变更**: 19 个字段命名 + 3 个类型修正
- **置信度**: 85
- **SceneMgr (5 字段)**:
  1. [A] +51696 `m_bRoleVisible` unsigned char: 3x refs, A0/88=byte (原标 float→修正)
  2. [A] +51648 `m_fScrollParam` float: 2x refs, 8B=dword in RoleSystem::_auto_414350
  3. [A] +51704 `m_nRenderMode` int: 2x refs, C7 05=store imm32
  4. [A] +51716 `m_bRenderFlag` unsigned char: 2x refs, 8A/88=byte
  5. [A] +51720 `m_fRenderParam` float: 2x refs, D9 05=fld float
- **CGameData (3 字段)**:
  1. [A] +736 `m_nMissionState` int: 4x dword refs
  2. [A] +3976 `m_nUIFlags` int: 4x refs
  3. [A] +624 `m_nPlayerMoney` int: 3x store/load refs
- **ScriptSystemData (11 字段)**:
  1. [A] +4008 `m_nCmdFA8` int: type unsigned char→int (binary confirms dword access)
  2. [A] +4104 `m_nCmd1008` int: type unsigned char→int
  3. [A] +4080 `m_pCmdTableFF0` int: 5x B9=mov ecx,addr (array base load)
  4. [A] +4172 `m_pCmdArray104C` int: 5x BF+[ecx*8+addr] (stride-8 array)
  5. 其余 7 个: 3-4x abs refs each, named with m_nCmd prefix

### [2026-05-13] 全局变量命名（11 个高引用）

- **变更**: 添加 11 个全局变量到 globals.json
- **置信度**: 80-85
- **证据**:
  1. [A] 0xC04380 `g_SceneArray` void*: 99 decomp refs, BF=mov reg,addr（基址加载）
  2. [A] 0xC04360 `g_RoleTeamArray` void*: 22 refs, 类似模式
  3. [A] 0x5D41B8 `g_fConst220` float: 39 refs, D9 05=fld; binary 读取值=220.0
  4. [A] 0x5D41BC `g_fConst200` float: 39 refs, D8 35=fdiv; binary 读取值=200.0
  5. [A] 0xBFDA78 `g_pSceneManager` void*: 12 refs, A3=store eax, 邻近 gfxMgr/g_pCBSystem
  6. [A] 0xDE5FA4 `g_nRoleState` int: 12 refs, A3=store eax
  7. 其余 5 个: 12 refs each, dword 访问确认 int 类型
- **float 值验证**: 直接读取 .rdata 段 binary 确认常量值（220.0/200.0）

### [2026-05-13] .data 段 float 全局变量 (11 个)

- **变更**: 11 个 .data 段 float 全局变量添加到 globals.json
- **置信度**: 85
- **证据**:
  1. [A] g_fGameTimer(0xBFDAA0): 13 hits, D9 05=fld float; Actor/EquipUI/CScreenMode 使用
  2. [A] g_fFadeAngle(0xBFDA58): 10 hits, D9 05=fld; PAL3::Render 中 `180.0 - flt` 模式
  3. [A] g_fTileScale(0xC12B14): 11 hits, 用作位置计算除数
  4. [A] g_fEffectTimer(0x58DE64): 13 hits, 累加 += dt, 重置 10.0
  5. 其余 7 个: 2-8 hits each
- **注意**: .rdata 常量（0x56A000-0x571000）由 gen_cpp LITERAL_MAP 处理，不在 globals.json 中

### [2026-05-13] .data 全局变量批量添加 (143 个)

- **变更**: 143 个 .data/.bss 段全局变量添加到 globals.json
- **置信度**: 85 (20 个手工命名), 70 (123 个自动命名 g_dword_/g_byte_ 模式)
- **方法**: 在 .text 段搜索 abs addr → 指令前缀解码确认访问宽度 → 3+ decomp refs 阈值
- **手工命名 (20 个)**: 从 decomp 上下文推断
  - [A] g_nEffShockCount (0x17A7E88): `++dword_` 模式 → 计数器
  - [A] g_pEffectSystem (0xBFDA70): PAL3::DestroyEffectSystem 读取 → 指针
  - [A] g_nRoleMoveParam (0xC02370): RoleSystem 读取
  - 其余 17 个效果/渲染/战斗计数器（++counter 模式）
- **自动命名 (123 个)**: g_dword_ADDR / g_byte_ADDR 格式
  - 有 binary 访问验证但 decomp 上下文不足以推断语义
  - 保留 IDA 地址后缀便于后续从代码中识别

### [2026-05-13] 123 个自动命名全局变量细化

- **变更**: 所有 g_dword_XXX/g_byte_XXX 模式替换为类上下文命名
- **置信度**: 75
- **方法**: 对每个变量在 decomp 中搜索引用函数，提取主要类名+使用模式（counter/flag/ptr/check），生成 g_n{Class}_{suffix} / g_b{Class}_{suffix} / g_pRenderEffect_{suffix} 等
- **类型修正**: 3x int→float（Rotate 上下文），5x int→gbRenderEffect*

### [2026-05-13] CEffMgr/st_Manager 清理 char[] 伪成员

- **变更**: CEffMgr 删除 418 个 char[] 伪成员（434→16），st_Manager 删除 14 个（26→12）
- **置信度**: 95
- **证据**:
  1. [A] CEffMgr 的 418 个 char[] 成员名字如 m_aDProjectPal3Co_3, m_aEndKey_87 等，是 IDA 自动标注的 .rdata 字符串常量地址被误认为结构体成员
  2. [A] CEffMgr 清理前 IDA parse_decl 失败（decl_len=21703，超过处理能力），清理后成功（decl_len~400）
  3. apply 日志确认：structs applied 802/806 → 803/806
- **全量扫描**: 检查所有 806 个结构体，确认仅 CEffMgr 和 st_Manager 有此问题；其余 175 个 char[N] 成员均为合法字段（name, ModelID, Remark 等）

### [2026-05-13] apply_annotations 错误报告增强

- **变更**: 失败的结构体现在打印 decl_len、member count、声明 preview
- **置信度**: N/A (工具改进)

### [2026-05-13] CCB 函数类归属修正 + 类型别名 + CCBSystem.m_pUtil

- **变更**:
  1. CCBSystem::GetStageRole → CCBStage::GetStageRole (sig this: CCBSystem*→CCBStage*)
  2. CCBSystem::GetStageRoleByIdx → CCBStage::GetStageRoleByIdx (sig this: CCBSystem*→CCBStage*)
  3. 10 个函数签名中 gbengine 类型别名修正 (GeomNode→gbGeomNode 等)
  4. CCBSystem+0 m_pUtil 类型 CCBSystem*→CUtil*
  5. 3 个占位结构体 (CCBUIPanel, MvcController, MvcViewport)
- **置信度**: 90 (函数归属), 90 (类型别名), 90 (m_pUtil)
- **证据 (函数归属)**:
  1. [A] GetStageRoleByIdx(0x4FC940): 函数体 `lea eax,[ecx+eax*8]` stride=2632 → CCBStage 的 task 数组
  2. [A] 同函数 `8B 09`=mov ecx,[ecx] 取 this[0]=CCBStage.m_pCBSystem(CCBSystem*)
  3. [A] 然后 `D9 41 50`=fld [ecx+0x50] → CCBSystem.m_fTimeFund (float) 确认
  4. [A] GetStageRole(0x4FC8F0): 同样 stride=2632 模式
  5. [A] CalcAttackPower 调用链: `8B 8B 0C020000`=mov ecx,[ebx+0x20C] → CCBRoleState.m_pStage(CCBStage*) → 调用 GetStageRoleByIdx
- **证据 (类型别名)**:
  1. [B] PDB 中 gbGeomNode/gbMatrix4/gbOBBox 等确认 gb 前缀
  2. [B] gbengine headers 中 class gbGeomNode/gbMatrix4 定义确认
- **证据 (m_pUtil)**:
  1. [B] PDB: CCBSystem+0x0 = CUtil * m_pUtil (非 CCBSystem *)
- **影响**: 签名失败 25→4, 战斗系统 cast 错误减少

### [2026-05-13] CCBUI::GetState/SetParam → CCBControl（二进制验证）

- **变更**: 2 个函数从 CCBUI 重分类到 CCBControl
- **置信度**: 90
- **证据**:
  1. [A] GetState(0x4DC560): `8A 41 25` = mov al,[ecx+0x25], ecx=this. CCBControl+0x25(37)=m_bForceRelease(unsigned char) 完美匹配
  2. [A] 调用者 CCBSystem::ProcMessage 通过 this->m_pControl(CCBControl*) 传入
  3. [A] SetParam(0x4DC5C0): `89 51 2C` = mov [ecx+0x2C],edx. CCBControl+0x2C(44)=tagControlData 区域
- **CCB cast 分析总结**:
  - 948 处 CCB cast 中: ~169 是 Hex-Rays 对大结构体内嵌 UIWnd 子对象的正常表示（(CCBUI*)((char*)this+offset)）
  - ~56 是通过 this->member 的跨类调用（部分归属错误，部分是正常的子系统委托）
  - 已修正 4 个函数归属（GetStageRole/ByIdx + GetState/SetParam）
  - 剩余高频 cast 需要逐个从二进制验证调用链

### [2026-05-13] 结构体成员批量填充（218 个新成员，8 个类）

- **变更**: 从二进制指令中提取 this+offset 访问，填充缺失的结构体成员
- **置信度**: 85 (偏移+类型从二进制确认), 50 (名字为 _field_ 占位)
- **方法**: 对每个类的所有 ClassName:: 方法，扫描函数体中 `[this_reg+disp8/disp32]` 模式，提取偏移和访问宽度（8B/89=dword, D9/DD=float, 8A/88=byte）
- **类和新增数**:
  1. CameraCtrl: 0→26 成员 (size=4088, 45 个方法, 56 个唯一偏移, 299 次访问)
  2. CScreenMode: 37→121 (+84) 成员 (size=4660)
  3. PalScriptMgr: +41 成员
  4. RenderTarget: 4→36 (+32) 成员 (size=200)
  5. PalScript: 9→25 (+16) 成员
  6. Object3D: 34→43 (+9) 成员
  7. UIScene: 45→52 (+7) 成员
  8. EquipUI: +3 成员
- **影响**: 消除大量 `this[N]` 越界访问（CameraCtrl 1695 处, CScreenMode 1636 处等）
- **注意**: 218 个新成员全部有 A 级二进制证据（指令中的 disp 值确认偏移），但名字是占位的，需要后续从代码语义推断命名

### [2026-05-13] CameraCtrl 补充偏移 + 语义命名

- **变更**:
  1. CameraCtrl 补充 33 个新偏移（修正扫描方法，覆盖 ecx 直接访问），总成员 26→59
  2. 2 个确认命名：m_nWidth(+472), m_nHeight(+476)
- **置信度**: 85 (偏移), 90 (命名: m_nWidth/m_nHeight)
- **证据 (命名)**:
  1. [A] SetDimention(0x41CA90): `89 81 D8010000` = mov [ecx+0x1D8],eax — 参数1(w)直接存入 +472
  2. [A] 同函数 `89 91 DC010000` = mov [ecx+0x1DC],edx — 参数2(h)直接存入 +476
  3. 函数签名 `void __thiscall(CameraCtrl *this, int w, int h)` 确认参数语义
- **回退**: m_pTarget/m_fFOV/m_nViewMode 等 5 个推断命名因仅有 D 级证据（领域知识推断）不达标，保留 _field_ 占位

### [2026-05-13] 结构体成员语义命名（12 个，二进制指令链验证）

- **变更**: 12 个 _field_ 成员从 setter 函数的二进制指令链中推断语义名
- **置信度**: 90
- **方法**: 读取 Set*/Init* 函数的完整指令链，追踪参数如何存入 this+offset
- **RenderTarget (6 个)**:
  1. [A] +24 `m_nHalfWidth`: SetSize(0x4B48E0) `mov eax,[esp+4]; cdq; sub eax,edx; sar eax,1; mov [ecx+0x18],eax` — param1/2
  2. [A] +28 `m_nHalfHeight`: 同函数 param2/2
  3. [A] +144 `m_nOffsetX`: SetOffset(0x4B4D80) `mov [ecx+0x90],eax` — param1
  4. [A] +148 `m_nOffsetY`: 同函数 `mov [ecx+0x94],edx` — param2
  5. [A] +152 `m_nScaleX`: SetScale(0x4B4DA0) `mov [ecx+0x98],eax` — param1
  6. [A] +156 `m_nScaleY`: 同函数 `mov [ecx+0x9C],edx` — param2
- **CScreenMode (3 个)**:
  1. [A] +68 `m_nPosX`: SetPosition(0x43DC40) `mov [ecx+0x44],eax` — param nX
  2. [A] +72 `m_nPosY`: 同函数 `mov [ecx+0x48],edx` — param nY
  3. [A] +4644 `m_state`: SetState `mov [ecx+0x1224],eax` — param state
- **CScreenMode (2 个, lea→call 推断)**:
  4. [A] +1284 `m_wndPanel1` UIWnd: lea [this+0x504]→ecx→call UIWnd::GetRect 确认嵌入 UIWnd
  5. [A] +1436 `m_wndPanel2` UIWnd: lea [this+0x59C]→ecx→call UIWnd::GetRect
- **UIScene (1 个, lea→call 推断)**:
  6. [A] +116 `m_pChildWnd` UIWnd*: lea [this+0x74]→ecx→call UIWnd::GetChildByIndex
- **UIScene (4 个, 类型修正)**:
  7. [A] 4 个 _field_ 类型 int→float: 二进制 fld 指令计数超过 mov dword 计数
- **CameraCtrl (3 个)**:
  1. [A] +460 `m_mode`: SetCamMode(0x41D5B0) `mov [ecx+0x1CC],eax` — param mode
  2. [A] +472 `m_nWidth`: SetDimention(0x41CA90) `mov [ecx+0x1D8],eax` — param w
  3. [A] +476 `m_nHeight`: 同函数 `mov [ecx+0x1DC],edx` — param h

### [2026-05-13] CCBSystem::GetDeltaTime/GetControl 重分类

- **变更**:
  1. CCBSystem::GetDeltaTime → CCBAttackSequen::SetFlag_1C5
  2. CCBSystem::GetControl → CCBControl::GetControl
- **置信度**: 90
- **证据**:
  1. [A] GetDeltaTime(0x4DB910): 完整函数体 `8A 44 24 04 88 81 C5010000 C2 0400` = mov al,[esp+4]; mov [ecx+0x1C5],al; ret 4. 这是一个 1-byte setter，不是 GetDeltaTime。CCBAttackSequen+0x1C5=tagAttackSequen[11]之后的 flag 字段。
  2. [A] 调用者 CCBSystem::ProcWeaponSkill 通过 this->m_pAttackSequen(CCBAttackSequen*) 传入
  3. [A] GetControl(0x4DC5B0): `8B 41 20 C3` = mov eax,[ecx+0x20]; ret. CCBControl+0x20(32)=m_nController(int) 完美匹配
  4. [A] 调用者通过 this->m_pControl(CCBControl*) 传入
- **累计 CCB 修正**: 6 个函数（GetStageRole/ByIdx + GetState/SetParam + GetDeltaTime + GetControl）

### [2026-05-13] CCBStageRole::IsActive → CCBRoleState（stride-892 扫描）

- **变更**: CCBStageRole::IsActive → CCBRoleState::IsActive
- **置信度**: 90
- **方法**: 搜索 .text 段中所有 stride=892 乘法链模式 `8D14C5 00000000 2BD0 C1E205 2BD0`，找到 33 处。其中 9 个函数非 CCBRoleState 归属，逐个验证后只有 IsActive 确认错分。
- **证据**:
  1. [A] IsActive(0x4ED040): 函数体使用 stride=892 乘法链访问 tagRoleState 数组 → this=CCBRoleState*
  2. [A] 调用者 CCBStageRole::ProcBlock 通过 this->m_pRoleState(CCBRoleState*) 传入
- **排除**:
  - HandleRoleStateDialog: 非 __thiscall（首条指令 A1=mov eax,[abs]），通过全局指针访问
  - DelTask: 函数开头 mov [ecx+0x19A4] → CCBStageRole 成员，stride-892 在函数后部（调用链）

### [2026-05-13] PDB 偏移伪影批量清理（345 个伪字段删除，12 个结构体）

- **变更**: 从 12 个 this-pointer 结构体中删除 345 个无二进制访问证据的 gap 来源字段
- **置信度**: 95（删除操作：字段在二进制中无访问即为伪影）
- **根因**: PAL3A.pdb 与 PAL3.exe 的结构体布局不匹配。PDB 导入 IDA 后产生的结构体偏移被 gap-fill 阶段用于插值，但这些偏移在 PAL3 二进制中不存在对应的 `[this_reg+disp32]` 访问指令。
- **验证方法**: 对每个结构体的所有 gap 来源字段（source 含 `gap_clean`/`gap_access`/`camblock_gap`），在该类所有方法的 .text 段二进制中搜索 `disp32` 作为 ModRM(mod=10) 操作数。无命中 → 伪字段。
- **证据**:
  1. [A] RoleSystem: IDA _field_2CC(offset 716) 在 154 个 RoleSystem 函数中 0 命中；CalcDirection 二进制实际访问 this+0x510（差值 0x244），确认 IDA 布局偏移
  2. [A] SceneMgrCamBlock: 140 个 gap 字段中仅 5 个有二进制命中（3.6%）
  3. [A] CCBStageScene: 16 个 gap 字段全部有二进制命中（0 伪字段），作为对照组确认方法可靠

| 结构体 | 清理前 | 清理后 | 删除数 | 伪影率 |
|--------|--------|--------|--------|--------|
| RoleSystem | 361 | 208 | 153 | 84% |
| SceneMgrCamBlock | 142 | 7 | 135 | 96% |
| CScreenMode | 122 | 109 | 13 | 48% |
| UIScene | 52 | 40 | 12 | 46% |
| UIListBox | 61 | 52 | 9 | 60% |
| UIAnimateCtrlEX | 24 | 12 | 12 | 85% |
| Actor | 49 | 42 | 7 | 28% |
| _Item_List_Info | 19 | 12 | 7 | 100% |
| ScreenEffectMgr | 20 | 15 | 5 | 83% |
| gbVolModNode | 8 | 3 | 5 | 100% |
| CCBUI | 78 | 76 | 2 | 50% |
| PAL3 | 32 | 30 | 2 | 50% |

- **影响**: 总成员数 968→606（-362），消除错误偏移字段对 IDA 结构体布局和代码生成的污染
- **后续**: 需要基于二进制分析重新填充这些结构体的有效成员（disp8 搜索、SIB 模式、间接访问链等方法）

### [2026-05-13] RoleSystem 二进制 disp32 重扫描（+25 新成员）

- **变更**: 对 154 个 RoleSystem 函数做 disp32 全量扫描，发现 25 个新偏移（已排除 disp8 假阳性）
- **置信度**: 85（偏移+类型从 ModRM+opcode 确认），50（名字为 `_todo_` 占位）
- **方法**: 识别每个函数头部 `mov reg, ecx` 确定 this 寄存器，扫描 `[this_reg+disp32]` (ModRM mod=10)，过滤对齐偏移，排除 overlap
- **排除**: +209(0xD1) 和 +523(0x20B) 因与相邻 int 字段 overlap 被移除（是 BYTE1 子字节访问）
- **命名约定**: 新增字段用 `_todo_XXX` 前缀，方便 `grep _todo_` 追踪待命名字段
- **高频字段**: +828(0x33C) 5funcs, +7432(0x1D08) 8hits/4funcs, +7280(0x1C70) 7hits/4funcs
- **影响**: RoleSystem 成员 208→233

### [2026-05-13] 5 个结构体 disp32 重扫描（+125 新 _todo_ 成员）

- **变更**: Actor(+20), CScreenMode(+39), UIListBox(+48), PAL3(+15), ScreenEffectMgr(+1) 添加二进制验证的占位成员
- **置信度**: 85（偏移+类型），50（_todo_ 占位名）
- **方法**: 同 RoleSystem 重扫描方法——识别 this 寄存器后搜索 `[this_reg+disp32]`，过滤对齐、排除 overlap
- **排除**: Actor +217(byte 子访问 overlap +216 int), +544(overlap m_dwMatMsg[11])
- **未扫描**: SceneMgrCamBlock/UIScene/UIAnimateCtrlEX(0 新成员), CCBUI/gbVolModNode(无 binary_size), _Item_List_Info(无函数)
- **影响**: 全部 _todo_ 字段总计 148 个（`grep -r '_todo_' structs/`）

### [2026-05-13] 21 个结构体批量 disp32 重扫描（+896 新 _todo_ 成员）

- **变更**: 对 21 个未扫描结构体执行 disp32 二进制全量扫描
- **置信度**: 85（偏移+类型），50（_todo_ 占位名）
- **方法**: 同前——识别 this 寄存器后搜索 `[this_reg+disp32]`，过滤对齐、排除 overlap
- **主要结果**:
  - Scene: +171（91 funcs，struct size=1094164）
  - GRPinput: +148（54 funcs，size=10584）
  - CCBRoleState: +100（204 funcs，size=23904）
  - PAL_GDB: +94（49 funcs，size=814524）
  - CCBStageRole: +74（106 funcs，size=6848）
  - CCBStage: +63（119 funcs，size=673992）
  - CCBStageScene: +48, PalScriptMgr: +29, EquipUI: +27, CEffMgr: +25
  - Camera: +22, CCBSystem: +21, RenderTarget2: +14, CCBAI: +13
  - CameraCtrl: +11, TextureLib: +11, Object3D: +9, NPC: +6, UIFrameWnd: +6
  - CCBStageCam: +3, RenderTarget: +1
- **未命中**: UIWnd(0), PalScript(0) — 已有成员已覆盖大部分访问
- **影响**: _todo_ 字段总计 148→1044（扫描原始数）

### [2026-05-13] 结构体数组/嵌入成员 overlap 修复（-399 伪成员）

- **变更**: 从 10 个结构体中删除 399 个落在已知数组/嵌入结构体内部的 _todo_ 字段
- **置信度**: 95（overlap 是确定性错误）
- **根因**: disp32 扫描找到的偏移可能是数组元素内部的成员访问（如 `this->m_obj[i].field`），表现为 `[this_reg + base_offset + i*stride + field_offset]`，被误认为顶层成员
- **修复明细**:
  - Scene: -167（m_obj[256] SceneObj 覆盖 224-456928, m_npc[72] Role 覆盖 456932+）→ 21 成员
  - CCBRoleState: -95（tagRoleState 数组内部）→ 27 成员
  - PAL_GDB: -49 → 51 成员
  - CCBStage: -36 → 63 成员
  - CCBSystem: -18 → 45 成员
  - CEffMgr: -16 → 24 成员
  - CCBAI: -8 → 15 成员
  - CCBStageRole: -4 → 149 成员
  - CCBStageScene: -4 → 114 成员
  - PalScriptMgr: -2 → 87 成员
- **影响**: _todo_ 字段总计 1044→649（净增 497 个有效新成员）

### [2026-05-13] 数组内部伪成员清理 + raw IDB 语义命名

- **变更**:
  1. 删除 213 个落在已知数组内部的 _todo_ 字段（GRPinput:148, CCBStageScene:32, Actor:20 等）
  2. 使用 raw IDB（无结构体导入）对 943 个函数做 Hex-Rays F5，获取原始偏移的反编译上下文
  3. 从 raw decomp 上下文推断 139 个 _todo_ 字段的语义名
- **置信度**: 95（数组清理），70（语义命名——基于 raw decomp 文本模式匹配）
- **方法**:
  - 数组清理：计算每个已知成员的覆盖范围（含数组），删除范围内的 _todo_
  - 语义命名：生成 raw IDB → F5 特定地址 → 匹配 `this + offset` 模式 → 从 strcpy/strlen/SetXxx 等上下文推断字段含义
  - 只保留高质量名称（排除 m_f_XXX/m_obj_XXX 等泛型模式）
- **命名策略**: strcpy→m_szXxx, sin/cos→m_fAngle, SetProgress→m_fProgressParam, byte flag→m_bXxx
- **影响**: _todo_ 649→436→297（最终剩余 297 个无法从上下文确定语义的字段）

### [2026-05-13] _field_ 旧占位 raw decomp 语义命名（149 个）

- **变更**: 对 363 个有 raw decomp 上下文的 _field_ 字段应用语义命名，149 个获得高质量名称
- **置信度**: 70（基于 raw Hex-Rays 文本模式匹配——strcpy/SetXxx/gbVec3D 等上下文）
- **方法**: 额外 F5 178 个函数（raw IDB 总计 1120 个），用同样的 `this + offset` 匹配 + 上下文推断
- **过滤**: 排除泛型名称（m_f_XXX/m_obj_XXX/m_szStr_XXX），只保留有明确语义的命名
- **影响**: _field_ 1140→991，命名率 84.4%→86.0%

### [2026-05-13] LODWORD 驱动的 float→int 类型修正（29 个字段）

- **变更**: 29 个标注为 float 但 raw decomp 中仅被 `*(_DWORD*)` 访问（0 次 float 访问，3+ 次 int 访问）的字段修正为 int
- **置信度**: 85（raw Hex-Rays 无结构体偏见，type cast 直接反映二进制访问模式）
- **方法**: 对每个 float 字段，在 1120 个 raw decomp 函数中计数 `*(float*)(this+N)` vs `*(_DWORD*)(this+N)` 出现次数。仅修正 float_uses=0 且 int_uses>=3 的确定性案例
- **典型修正**:
  - CCBStageRole+528 m_fLeftWeapon: 14x int, 0x float → int
  - CEffectSystem+336 m_fWindDirection: 45x int, 0x float → int
  - Role+1392 m_curforce: 20x int, 0x float → int
- **排除**: RoleSystem+4/8/12 (m_fTargetX/Y/Z) 有 260+ float 用法和 500+ int 用法，是 union 模式，保留 float
- **影响**: 消除生成代码中 ~200 个 LODWORD() 包装

### [2026-05-13] CCBStageRole.m_fBlend float→int（最大 LODWORD 贡献者）

- **变更**: CCBStageRole+284 m_fBlend float → m_nBlendState int
- **置信度**: 90
- **证据**:
  1. [A] raw decomp 中 51 次 `*(_DWORD*)(this+284)` vs 1 次 `*(float*)(this+284)`
  2. [A] 使用模式: `== 2`, `== 1`, `== 0` 整数比较 → 状态枚举，非浮点值
- **影响**: 消除生成代码中 132 个 LODWORD(this->m_fBlend) 包装

### [2026-05-13] PAL3::FullInit 全局变量补充（10 个）

- **变更**: 为 PAL3::FullInit 核心初始化函数补充 10 个全局变量到 globals.json
- **置信度**: 80
- **证据**:
  1. [A] 0x586180-58619C: raw decomp 中 `sub_4125D0(dword_BFDBB0, &off_586180)` + `strcpy(word_BFDC5E, off_586180)` → 场景名字符串指针
  2. [A] 0xDE5220: `memset(byte_DE5220, 0, 0x28)` → 40 字节存档标记数组
  3. [A] 0xC04334: `memset32(dword_C04334, 20, 6)` → 6 元素 int 数组（角色初始等级=20）
  4. [A] 0xC020F0: `while (v0 < &byte_C020F0)` → ScriptCounter 数组结束边界
- **背景**: FullInit 引用 465 个全局地址，其中 369 个在 g_SceneMgr 内部（需编译阶段视图转换），70 个独立全局变量缺失（已补 10 个，剩 14 个需更多上下文分析）
- **影响**: FullInit 中 dword_ 残留减少

### [2026-05-13] FullInit 独立 RoleSystem 实例发现（+7 全局变量）

- **变更**: 发现 3 个独立 RoleSystem 全局实例 + 4 个相关全局变量
- **置信度**: 90
- **证据**:
  1. [A] 0xBFDBB0 与 0xBFFDB0 相隔 8704 字节 = RoleSystem size → 连续两个 RoleSystem 实例
  2. [A] BFDBB0+174=BFDC5E → `strcpy(word_BFDC5E, scene_name)` 确认 name 字段位置
  3. [A] BFDBB0+1264=BFE0A0 → `dword_BFE0A0 = 1` 对应 RoleSystem.m_nMoveMode (+1264)
  4. [A] BFDBB0+632=BFDE28 → 对应 RoleSystem.m_pRoleObj (+632)
  5. [A] C020F8+174=C021A6 → `strcpy(word_C021A6, scene_name)` 确认第三个实例
  6. [A] C020F8+172=C021A4 → `byte_C021A4 = 5` 对应 RoleSystem.m_nFacing (+172)
- **新增全局变量**:
  - g_RoleSystemExtra0 @ 0xBFDBB0 (RoleSystem)
  - g_RoleSystemExtra1 @ 0xBFFDB0 (RoleSystem)
  - g_RoleSystemMain @ 0xC020F8 (RoleSystem)
  - g_nPathEnabled @ 0xC02374, g_nRoleMoveLock @ 0xC025E8
  - g_pRoleTeam0_Capacity @ 0xC0435C, g_pRoleTeam1_Capacity @ 0xC0436C
- **影响**: FullInit 中 14 个独立全局变量全部标注完成

### [2026-05-13] ScriptSystemData 命令表数组化（-372 _field_）

- **变更**: 将 ScriptSystemData 偏移 4432-7852 的 372 个独立 _field_ 替换为 `m_CmdTable tagScriptCmd[213]`
- **置信度**: 90
- **证据**:
  1. [A] stride-16 模式: 51 个条目有 short(+0)+int(+4)+int(+8) 一致结构
  2. [A] 从 CHANGE_LOG 早期记录: sub_4329B0 命令表区域，stride=16，赋值全用绝对地址
  3. [A] 30 个条目有 abs_ref 二进制证据（`66 89 3D`=mov word, `89 0CC5`=mov [ecx*8+addr] 等）
- **新增结构体**: tagScriptCmd {short cmd_id; short _pad; int handler; int param; int flags;} size=16
- **影响**: ScriptSystemData 成员 556→185, 总 _field_ 991→619, 命名率 86.0%→89.6%
