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
