# PAL3patch 结构体定义导入总结

## 概述

PAL3patch 是 zhangboyang 的开源逆向项目，包含高质量的游戏结构体定义。
位置：`extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h`（1872 行）

## 解析结果

共解析出 **110 个结构体定义**，包括：

### 基础类型
- `gbVec3D` (12 bytes): float x, y, z
- `gbQuaternion` (16 bytes): float x, y, z, w
- `gbMatrix4` (64 bytes): 4x4 矩阵
- `gbColorQuad` (4 bytes): 颜色值
- `PtrArray` (16 bytes): 动态指针数组

### UI 类
- `UIWnd` (68 bytes) — **完全匹配我们的 annotations (0-64 offsets)**
- `UIFrameWnd` (1 field)
- `UIStatic` (16 fields)
- `UIButton` (16 fields)
- `UIListBox` (18 fields)
- `UIScrollBar` (16 fields)
- `UIProgressBar` (34 fields)
- `UIDialog`, `UITextArea`, `UIRoleSelect` 等

### 战斗系统类
- **`CCBUI`** (24 fields) — 战斗UI，包含大量语义字段名
  - 攻击序列面板指针数组
  - 角色状态面板指针数组（4个角色）
  - 各种状态图标（攻击↑↓、防御↑↓、幸运、速度、眠、乱、禁等19种状态×11个格子）
  - 血条/气条/神条进度条（HP/GP/MP）
  - 胜利/失败面板
  - 战斗结果面板（升级、获得物品等）
- `CCBSystem` (30 fields)
- `CCBAttackSequen` (7 fields)
- `tagRoleState`/`CCBRoleState`
- `tagCmdData`

### 3D 渲染类
- `gbCamera` (12 fields)
- `ObjectCamera` (13 fields)
- `gbGfxManager_D3D` (26 fields)
- `RenderTarget` (2 fields)
- `gbTexture`, `gbTexture_D3D`

### 其他游戏逻辑类
- `ScriptData`, `RestScript`, `TxtFile`
- `CPK`, `CPKHeader`, `CPKTable` (CPK 文件系统)
- `SoundMgr`, `gbAudioManager` (音频)
- `HeadMsg`, `UIEmote` (头顶消息、表情)
- `UIGameFrm`, `UISceneFrm`, `UIGameOver`

## 关键发现

### 1. UIWnd 定义验证

PAL3patch UIWnd (68 bytes):
```
   0: UIWndVtbl *          vfptr
   4: gbColorQuad          m_fontcolor
   8: gbColorQuad          m_wndcolor
  12: DWORD                m_id
  16: RECT                 m_rect
  32: UIWnd *              m_pfather
  36: PtrArray             m_childs
  52: int                  m_bcreateok
  56: int                  m_bvisible
  60: int                  m_benable
  64: int                  m_bfocus
```

**结论**：我们的 annotations (88 bytes) **更完整**，包含 offset 68-87 的额外字段：
- 68: _todo_044 (unsigned char)
- 72: _todo_048 (int)
- 76: m_fScaleX (float)
- 80: m_fScaleY (float)
- 84: _todo_054 (int)

offset 0-64 的定义**完全一致**（类型/偏移都匹配）。

### 2. 类型对应关系

| PAL3patch | annotations | 说明 |
|-----------|-------------|------|
| DWORD | unsigned int | 等价 |
| RECT | tagRECT | 等价 |
| UIWndVtbl * | int (vfptr) | annotations 简化为 int |
| struct T | T | annotations 不使用 struct 前缀 |

### 3. 我们 annotations 的优势

- **更完整的字段覆盖**：UIWnd 88 bytes vs PAL3patch 68 bytes
- **已有正确的类型**：offset 52-64 的 int 字段（之前误报为 float，现已修正）
- **包含运行时字段**：如 m_fScaleX/Y（缩放因子，PAL3patch 可能不关注）

## 导入策略

### 阶段 1：验证已有定义（完成）

✓ UIWnd 验证通过，offset 0-64 完全匹配

### 阶段 2：导入语义字段名（进行中）

对于包含 `_todo_` / `_field_` 占位符名称的字段，如果 PAL3patch 有对应偏移的语义名称，则导入。

**优先处理的结构体**：
1. **CCBUI** — 战斗UI，24个字段，全部有语义名称
2. **UIStatic** — 16个字段
3. **UIButton** — 16个字段
4. **UIListBox** — 18个字段
5. **UIProgressBar** — 34个字段
6. **CCBSystem** — 30个字段

### 阶段 3：填补空白结构体（TODO）

对于 annotations 中完全缺失的结构体，从 PAL3patch 创建初始定义：
- gbVec3D
- gbQuaternion
- gbCamera
- gbAudioManager

## 工具

已创建：
- `pipeline/parse_pal3patch_structs.py` — 解析 pal3.h 结构体定义
- `pipeline/merge_pal3patch_names.py` — 合并字段名到 annotations

## CCBUI 布局冲突发现（2026-05-21）

### 问题

尝试导入 CCBUI 字段定义时发现：**PAL3patch 和我们的 annotations 的偏移完全不匹配**。

| 对比项 | PAL3patch | Our annotations |
|--------|-----------|-----------------|
| 总大小 | 2688 bytes | 3552 bytes |
| CCBUI 自身 | 2536 bytes | 3400 bytes |
| offset 152 | m_pAttackSequenBack | (无) |
| offset 156 | m_pAttackSequenFace[11] | m_nTargetHeight (float) |
| offset 164 | (无) | m_pRoleStateFace[3] |
| offset 200 | m_pRoleStatePanel[4] | (无) |
| offset 216 | m_pRoleStateFace[5] | (无) |
| offset 256 | union of 19 states | (无union结构) |

### 证据来源分析

我们的 CCBUI annotations 有 77 个字段，来源分布：
- PDB: 34 个（来自 PAL3A，不一定适用于 PAL3）
- binary: 20 个（从 PAL3.exe 二进制验证）
- A/A+ (binary): 10 个（高置信度二进制证据）
- inferred: 9 个（推断）
- fix/gap: 3 个（修正/填充）
- ida_decomp: 1 个（IDA 反编译推断）

关键字段的证据：
- offset 156 (m_nTargetHeight): `A:FPU_disp32_0x518827` — **A 级二进制证据**
- offset 176 (m_nWindowX): `binary:SetSelection` — **二进制验证**
- offset 180 (m_nWindowY): `A:FPU_disp32_0x441937` — **A 级二进制证据**

### 原因分析

1. **PAL3A vs PAL3**：我们的 annotations 大量来自 PAL3A PDB，而 PAL3patch 逆向的是 PAL3.exe。PAL3A 和 PAL3 的结构体布局可能不同。
2. **版本差异**：PAL3 有多个版本（简体中文、繁体中文、日文等），可能有不同的结构体布局。
3. **字段差异**：我们的 CCBUI 比 PAL3patch 多 864 bytes，可能包含了额外的字段（如 m_nTargetHeight, m_nWindowX, m_nWindowY 等）。

### 结论

**不能直接批量导入 CCBUI 字段定义**。偏移不匹配说明这是不同的结构体布局。

### 正确策略

1. **保留有二进制证据的字段**：offset 156, 176, 180 等有 A/A+ 级证据的字段必须保留
2. **UIWnd 等基础类可以导入**：如果偏移匹配且类型一致
3. **PAL3patch 作为命名参考**：对于语义不明确的字段，可以参考 PAL3patch 的命名方式，但不能直接替换偏移
4. **需要二进制验证**：对于重要的结构体（如 CCBUI），需要从 PAL3.exe 二进制中验证实际的字段偏移

## 最终策略（2026-05-21）

经过验证，**PAL3patch 和我们的 annotations 偏移不匹配**，说明它们来自不同版本或不同的逆向分析：

1. **保留现有定义** — 我们的 annotations 有大量 A/A+ 级二进制证据，不能被覆盖
2. **UIWnd 无需导入** — 我们的定义已优于 PAL3patch（88 vs 68 bytes）
3. **CCBUI/UIStatic 不能批量导入** — 偏移完全不匹配（CCBUI: 3552 vs 2688 bytes）
4. **导入基础类型** — gbVec3D, gbQuaternion, gbColorQuad 等在我们的 annotations 中不存在，可以从 PAL3patch 创建
5. **PAL3patch 作为命名参考** — 对于语义不明确的字段，可以参考 PAL3patch 的命名方式，但不能直接替换偏移

## 已完成的工作

1. ✓ 创建 `pipeline/parse_pal3patch_structs.py` — 解析 pal3.h 结构体定义
2. ✓ 创建 `pipeline/merge_pal3patch_names.py` — 合并字段名工具（带 UIWnd + CCBUI 定义）
3. ✓ 创建 `pipeline/ccbui_fields.py` — CCBUI 完整字段列表（53 个字段，手动计算偏移）
4. ✓ 创建 `pipeline/verify_pal3patch_match.py` — 验证偏移匹配情况
5. ✓ 创建 `pipeline/import_basic_types.py` — 从 PAL3patch 导入基础类型
6. ✓ 验证 UIWnd offset 0-64 完全匹配
7. ✓ 发现 CCBUI 偏移不匹配（3552 vs 2688 bytes）
8. ✓ 统计 CCBUI 证据来源（34 个 PDB, 20 个 binary, 10 个 A/A+）

## 工具使用

```bash
# 解析 PAL3patch 结构体（只读分析）
python pipeline/parse_pal3patch_structs.py

# 验证偏移匹配情况
python pipeline/verify_pal3patch_match.py

# 导入基础类型（gbVec3D, gbQuaternion, gbColorQuad）
python pipeline/import_basic_types.py
python pipeline/check_annotations.py  # 验证
```

## 不推荐的操作

- ✗ 批量替换现有结构体的偏移（会丢失二进制证据）
- ✗ 假设 PAL3patch 的偏移适用于我们的 PAL3.exe（版本可能不同）
- ✗ 用 PDB 数据覆盖有 A/A+ 级二进制证据的字段

## 参考

- PAL3patch 项目：https://github.com/zhangboyang/PAL3patch
- 定义文件：`extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h`
- 逆向笔记：`extra/PAL3patch/notes/pal3/known_classes.txt`
