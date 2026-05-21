# PAL3patch 结构体定义验证总结

## 验证方法论

**关键原则**（用户提供）：
1. PAL3patch 的 **size 不可信** — 它只关注需要 patch 的字段，可能缺失尾部
2. 应关注 **已定义字段的准确性**，而非结构体总大小
3. 如果二进制证据证明 PAL3patch 正确，可提高置信度甚至直接导入

## 验证结果

### 1. PtrArray ✅ **高置信度 — 可直接导入**

| 指标 | 结果 |
|------|------|
| 大小匹配 | ✓ 16 bytes |
| 字段匹配率 | 75% (3/4) |
| 唯一差异 | offset 0: `buf` (PAL3patch) vs `m_pData` (Ours) |

**结论**：
- PAL3patch 定义**准确且完整**
- `buf` 比 `m_pData` 更简洁
- **操作**：可以导入 PAL3patch 的字段名

### 2. UIWnd ✅ **部分可导入 (offset 0-64)**

| 指标 | 结果 |
|------|------|
| PAL3patch 大小 | 68 bytes |
| 我们的大小 | 88 bytes |
| 字段匹配率 (0-64) | 90.9% (10/11) |
| 我们的额外字段 (68-84) | 有 A+/A 级二进制证据 |

**结论**：
- PAL3patch 的 offset 0-64 **准确但不完整**（符合预期：只记录需要的字段）
- 我们的 offset 68-84 有独立的二进制证据（m_fScaleX/Y 等）
- 两者**不矛盾**，可以共存

**操作**：
- 可以用 PAL3patch 优化 offset 0-64 的字段名（如果有差异）
- 保留我们的 offset 68-84 字段

### 3. UIFrameWnd ⚠️ **base_size 差异导致偏移错位**

| 对比项 | PAL3patch | Ours |
|--------|-----------|------|
| UIWnd base | 68 bytes | 88 bytes |
| UIFrameWnd 总大小 | 152 bytes | 152 bytes ✓ |
| offset 68/88 | char[80] szframe | _todo_58 (float) |
| offset 148 | int m_frameid | float m_nBorderStyle |

**关键问题**：base_size 不同（68 vs 88）导致 UIFrameWnd 自身字段的偏移不对齐。

**offset 148 二进制验证**：
- Int 访问: **92 次**（mov [reg+0x94]）
- Float 访问: 35 次（其中大部分是 `fild` = int→float 转换）
- **结论**: offset 148 应该是 **int**（PAL3patch 正确）

**offset 68/88 验证**：
- 未找到明确的 LEA [reg+0x58] 或 LEA [reg+0x44] 访问
- 无法直接验证是否是 char[80] 字符串缓冲区

**当前状态**：
- offset 148: 我们标注为 float，应修正为 int
- offset 68/88: 需要更多验证（可能需要 IDA 反编译上下文）

## 类型判定关键发现

### FPU 指令 ≠ float 字段

| 指令 | 操作 | 字段类型 |
|------|------|---------|
| `fld` (D9) | 加载 float | **float** |
| `fild` (DB) | 加载 int→float | **int** ❌ 常被误判 |
| `fst` (D9) | 存储 float | **float** |
| `fist/fistp` (DB) | 存储 float→int | **int** |

**教训**：
- 之前把所有 FPU 访问都当作 float，导致 **系统性类型错误**
- 必须区分 `fld` (真 float) 和 `fild` (int 转换)

**已知类型错误**：
1. CCBUI offset 156: 标注 float，实际 int (fild 证据)
2. CCBUI offset 180: 标注 float，实际 int (fild 证据)
3. UIFrameWnd offset 148: 标注 float，实际 int (92 mov vs 35 fild)

## 置信度评估

### 高置信度（≥90%）— 可直接导入

- **PtrArray** (100%): 大小匹配 + 字段准确

### 中高置信度（80-90%）— 可导入部分

- **UIWnd offset 0-64** (91%): 字段准确但不完整

### 需要更多验证（<80%）

- **UIFrameWnd**: base_size 差异导致无法直接对比
- **CCBUI**: 大量 PDB 来源字段，需逐一验证

## 建议的导入策略

### 立即可执行

1. **PtrArray**：
   ```json
   offset 0: buf (void **) — 替换 m_pData
   ```

2. **UIWnd offset 0-64**：
   - 保持现有定义（已经匹配）
   - 如果有命名差异，用 PAL3patch 的语义名称

### 需要修正后导入

1. **UIFrameWnd offset 148**：
   ```
   当前: float m_nBorderStyle
   修正: int m_frameid
   证据: 92 mov 访问 vs 35 fild 访问
   ```

2. **CCBUI offset 156/180**：
   ```
   offset 156: float m_nTargetHeight → int
   offset 180: float m_nWindowY → int
   证据: fild (DB) 指令 = int→float 转换
   ```

### 暂不导入（需深度验证）

- **CCBUI 全量布局**：偏移差异太大（2688 vs 3552），需要逐字段二进制验证
- **UIFrameWnd offset 68/88**：未找到明确访问模式

## 下一步行动

### 优先级 1：修正已知类型错误

1. UIFrameWnd offset 148: float → int
2. CCBUI offset 156: float → int
3. CCBUI offset 180: float → int

证据充分，可直接修正。

### 优先级 2：导入高置信度字段

1. PtrArray offset 0: m_pData → buf

### 优先级 3：深度验证 CCBUI

- 针对 PAL3patch 的 CCBUI 字段逐一做二进制验证
- 确认函数归属（0x518827, 0x441937 等是否真的访问 CCBUI）
- 重新评估整体布局

## 工具链

已创建的验证工具：
- `pipeline/validate_pal3patch_structs.py` — 自动化结构体对比
- `pipeline/verify_ccbui_conflict.py` — CCBUI 字段二进制验证
- `pipeline/verify_uiframewnd.py` — UIFrameWnd offset 148/68 验证

## 参考

- PAL3patch 源码: `extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h`
- 验证报告: `docs/ccbui_conflict_analysis.md`
- 导入总结: `docs/pal3patch_import_summary.md`
