# 元素尺寸 ≠ 宿主类尺寸（2026-10-21 R62-R65 连环误归属定谳）

## 起因：896B 三连环误归属

| 轮 | 误判 | 真相 |
|---|---|---|
| R62 | 896B = **Actor** | ❌ |
| R64 | 896B = **UIManager** | ❌（UIManager binary_size=**4**，无 RoleSlot 成员）|
| **R65** | — | ✅ **896B = tagRoleSlot 元素尺寸** |

**真数组 = `Scene.m_roleSlots tagRoleSlot[64]`（57344B 实读）**

## 机制

**「元素尺寸」与「宿主类尺寸」是两个不同概念**：

```
宿主类 Scene {
    tagRoleSlot m_roleSlots[64];   // ← 元素型 tagRoleSlot（896B）
}                                   //   宿主类 Scene（含 64×896B 数组）

896 = tagRoleSlot 的 binary_size（元素尺寸）
≠ Scene 的 binary_size（宿主类尺寸）
≠ UIManager 的 binary_size（无关类）
```

**误判模式**：看到「896B 数组」就问「哪个类是 896B？」——错！
**正确模式**：看到「896B 数组」要问「**哪个类含 896B 元素的数组**？」

## 判据

| 问题 | 对 | 错 |
|---|---|---|
| 896B 数组的元素是什么型？ | `tagRoleSlot`（896B）| — |
| 896B 数组的宿主类是什么？ | `Scene`（含 `m_roleSlots[64]`）| ~~Actor/UIManager~~ |
| 宿主类的尺寸？ | Scene 的 binary_size | ~~896~~ |

## 教训链（R62-R65）

1. **R62**：vtable 0x56AAC4 → 「Actor 表族」→ 896B=Actor ❌
2. **R64**：globals.json g_UIManager → 896B=UIManager ❌（UIManager 只有 4B）
3. **R65**：tagRoleSlot binary_size=896 双证 → **896B=元素尺寸** ✓

**根因**：每轮都把「元素尺寸」当「宿主类尺寸」找归属。

## 防范

1. **先分清元素 vs 宿主**：数组的 `T[N]` 里 T 是元素型，N 是元素数，宿主是含该数组的类
2. **查 binary_size 语义**：`tagRoleSlot.binary_size=896` 是**元素**尺寸，非宿主
3. **连环误归属要警惕**：同一数字反复误归属 ⇒ 问题在**概念**不在**数据**

## 关联

- **P0-6 改型纪律**：[method_function_signature_inference.md](method_function_signature_inference.md) §7
- **证据分级**：[rule_evidence_tiering_no_unobtainable_gate.md](rule_evidence_tiering_no_unobtainable_gate.md)
