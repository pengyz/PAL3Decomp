# CCBUI 结构体冲突深度分析

## 问题背景

PAL3patch 和我们的 annotations 在 CCBUI 结构体定义上存在重大差异：
- PAL3patch: 2688 bytes
- Our annotations: 3552 bytes（差 864 bytes）

## 二进制验证结果（2026-05-21）

### Offset 156 验证

```
Source: data/annotations/structs/CCBUI.json
  offset: 156
  name: m_nTargetHeight
  type: float  ❌
  evidence: A:FPU_disp32_0x518827

Binary: original/PAL3.exe @ 0x518827
  Bytes: DB 80 9C000000
  Disasm: fild dword [eax+0x9C]
  Disp32: 0x9C = 156 ✓

结论:
  ✓ offset 156 确实存在
  ✗ 类型错误：应该是 int，不是 float
  ? 需要确认 eax 是否指向 CCBUI
```

**关键**：`fild` (DB) = 加载 **int** 并转换为 float，不是直接加载 float。

### Offset 180 验证

```
Source: data/annotations/structs/CCBUI.json
  offset: 180
  name: m_nWindowY
  type: float  ❌
  evidence: A:FPU_disp32_0x441937

Binary: original/PAL3.exe @ 0x441937
  Bytes: DB 86 B4000000
  Disasm: fild dword [esi+0xB4]
  Disp32: 0xB4 = 180 ✓

结论:
  ✓ offset 180 确实存在
  ✗ 类型错误：应该是 int，不是 float
  ? 需要确认 esi 是否指向 CCBUI
```

## FPU 指令类型判别

| 指令 | 操作 | 字段类型 |
|------|------|---------|
| `fld` (D9) | 加载 float | **float** |
| `fild` (DB) | 加载 int→float | **int** |
| `fst` (D9) | 存储 float | **float** |
| `fist` (DB) | 存储 float→int | **int** |

**教训**：FPU 访问不等于 float 字段。必须区分 fld 和 fild。

## PAL3patch vs Our Annotations（offset 152-256）

| Offset | PAL3patch | Our Annotations | 证据等级 |
|--------|-----------|-----------------|---------|
| 152 | m_pAttackSequenBack (UIStatic *) | (无) | - |
| 156 | m_pAttackSequenFace[11] | m_nTargetHeight (**int** ❌标为float) | 🔴 A |
| 164 | (无) | m_pRoleStateFace[3] | ⚪ PDB |
| 176 | (无) | m_nWindowX (int) | 🟡 binary |
| 180 | (无) | m_nWindowY (**int** ❌标为float) | 🔴 A |
| 184 | (无) | m_pRoleStateFaceName[5] | ⚪ PDB |
| 200 | m_pRoleStatePanel[4] | (无) | - |
| 204 | (无) | m_pRoleStateAttackInc[11] | ⚪ PDB |
| 216 | m_pRoleStateFace[5] | (无) | - |
| 248 | (无) | m_pRoleStateAttackDec[11] | ⚪ PDB |
| 256 | union of 19 states | (无) | - |

## 可能的解释

### 假设 1：两者访问不同的对象

- 我们的 offset 156/180 访问的是其他结构体（如 UIFrameWnd），不是 CCBUI
- PAL3patch 的 offset 152-256 是 CCBUI 真实布局

**验证方法**：
1. 查看 0x518827 和 0x441937 所在函数的签名
2. 确认函数是否属于 CCBUI 类（vtable 归属）
3. 确认 eax/esi 是否来自 ecx (this 指针)

### 假设 2：CCBUI 有多个版本/配置

- 不太可能，PAL3 版本单一

### 假设 3：我们的 annotations 混入了其他类的字段

- offset 156/180 可能是 UIFrameWnd 基类的字段
- UIFrameWnd 是 152 bytes，offset 156 在 UIFrameWnd 范围内

**验证方法**：
```python
# 检查 UIFrameWnd 是否有 offset 156-152=4 的字段
# UIFrameWnd base_size = 152
# offset 156 in CCBUI = offset 4 in UIFrameWnd extension
```

但 UIFrameWnd 只有 152 bytes，offset 156 已经超出了。

## 下一步行动

1. **确认函数归属**：
   ```bash
   # 查询 0x518827 和 0x441937 所在函数
   # 检查函数是否在 CCBUI vtable 中
   python pipeline/ida/query_function_class.py 0x518827 0x441937
   ```

2. **确认 this 指针来源**：
   - 读取函数头部，确认 eax/esi 是否来自 ecx
   - 如果不是，说明访问的不是 CCBUI

3. **重新审视整个 CCBUI 布局**：
   - 如果 offset 156/180 不属于 CCBUI，需要删除
   - 如果属于 CCBUI 但类型错误，需要修正为 int
   - 评估 PAL3patch 的布局是否是正确的基准

4. **批量验证 PDB 来源字段**：
   - offset 164, 184, 204, 248, 292 等都来自 PAL3A PDB
   - 需要从 PAL3.exe 二进制验证它们是否存在

## 初步结论

**我们的 annotations 可能有系统性错误**：
1. 类型标注错误（fild 误判为 float）
2. 可能混入了其他类的字段
3. 大量依赖 PAL3A PDB（不一定适用 PAL3）

**PAL3patch 的可信度更高**：
1. 直接从 PAL3.exe 逆向
2. 是 patch 项目，只关注它 patch 的点（信息可能不完整但准确）
3. 结构体大小更合理（2688 vs 3552）

**建议**：
- 以 PAL3patch 为基准，重新验证 CCBUI 的每个字段
- 对于冲突字段，做二进制二次验证（不能简单保留我们的）
- 修正已知的类型错误（offset 156/180: float→int）
