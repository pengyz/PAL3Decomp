# N3/N4 新发现（2026-10-09 · 落地 N1+N6a 期间的只读调查）

## 结论：N3/N4 不是"codegen 缺 cast 规则"，是 **IDB enum 类型注入链**的两个不同失效点

### 机理链（已逐环实证）
```
data/annotations/enums.json  声明 enum
    → apply_annotations 写进 IDB
    → Hex-Rays 认识该 enum
    → 目标类型是 enum 且实参是整型时自动补 cast   ← 实证：decomp 里 (EEffect)1 / (ECBRoleSpecState)...
    → 生成码带 cast ⇒ 编译通过
```
**实证**（`asm/pal3/decomp/` 全量扫描）：
- `CEffect_CreateOneParticalfloat_004c7150.json:130` `v2->m_eKind = **(EEffect)1**;` —— **Hex-Rays 对整型字面量补 enum cast**
- `CCBAI_DemandThreadTracervoid_004d94f0.json:46` `v4[2].eSpecState = **(ECBRoleSpecState)**FindFirstEnemySlot(...);`

⇒ **Hex-Rays 会补 enum cast**，复核者说的"codegen 从未实现 enum cast 规则"是**对 codegen 而言正确，但不完整**——真正的补 cast 发生在 Hex-Rays 侧，前提是 **IDB 知道目标类型是 enum**。

### N3（`CPK::SetOpenMode`）失效点 = **导入类型注入链**
| 环 | 状态 |
|---|---|
| `ECPKMode` 在 `enums.json` | ✅ 已有（`CPKM_Null=0 … CPKM_End=4`）|
| `CPK::SetOpenMode` 的签名 | ✅ 在 `data/gbengine_registry.jsonl:1044`（mangled `?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z`，**A 级**：装饰名直接编码形参 `W4ECPKMode`）|
| 注入机制 | ✅ 存在：`pipeline/ida/apply_annotations.py:1618 import_gbengine_types()`「Set correct function types on gbengine IAT entries」|
| **实际生效** | ❌ **未生效**（生成码仍 `SetOpenMode(1)` 裸字面量）|

⇒ **下一步**：定位 `import_gbengine_types` 为何漏了这个 IAT 槽（覆盖面？`ECPKMode` 解析失败？还是注入了但 Hex-Rays 对 literal 不补？）。**属诊断，非补丁**。

### N4（`gbMatrix4::SetAxisAngle`）失效点 = **`gbAxis` enum 缺失**
```
gbAxis: MISSING   ← data/annotations/enums.json 里根本没有 gbAxis
```
⇒ Hex-Rays 不认识 `gbAxis` ⇒ 不补 cast ⇒ `SetAxisAngle(2, ...)` 裸整型。
⇒ **v1 的"重载集不完整"被证伪是对的，但真正的根因既非重载也非 codegen，而是 `gbAxis` 未声明**。
⇒ **最小修法**：在 `enums.json` 补 `gbAxis`（须二进制/真源证据给全枚举值），叠加 `LODWORD(float)` 位保持问题（见 REVIEW_v2 §3.1）。

### 对复核裁决的补充（非推翻）
- codex「codegen 从未实现 enum cast 规则」—— **对 codegen 正确**，但若 IDB 类型注入到位，**codegen 可能根本不需要这条规则**（Hex-Rays 侧已补）。
- ⇒ N3/N4 的修法优先级应是 **annotation/enums + 导入类型注入**，而非 codegen 新规则。

## 本轮已落地（不含 N3）
| 项 | 状态 | 门禁 |
|---|---|---|
| **N1** `UIPushButton::FormatText/LoadTexture` 签名 | ✅ 已改 | `annotation_diff`=1 结构体 2 处 · `check_annotations` **0 errors PASS** · `audit_type_layout --only UIPushButton` 仅 `__tail_drift__`（既有）|
| **N6a** `_nearby_532a30` → `global_init_stub_00532A30` | ✅ 已改 | 同上 |
| **N3** | ⏸ 暂缓 | 需先诊断 `import_gbengine_types` 失效点（非补丁）|
