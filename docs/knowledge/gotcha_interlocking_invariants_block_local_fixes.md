---
name: gotcha-interlocking-invariants-block-local-fixes
description: vtable 解析子系统里 owner 提取 / self 实参丢弃 / stub 签名约定三者互锁——只修"owner 前缀截断"这一处，会被另两条不变式抵消并净增 17 条 C2660；同一实验在两层各做一次，结果一致
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：互锁的不变式会让"局部正确修复"净亏

## 现象

生成代码里有"丢 owner 前缀"的病灶 ✓：

```cpp
// decomp 原文（正确 ✓）：this->me_Role[2].m_RoleAttCng[0].pDebugTex
// 生成代码（错 ✗）  ：((...))pDebugTex->IsLoaded)(...)
pal3/src/Misc/MainEquipUI.cpp:314  ·  pal3/src/Misc/SaleUI.cpp:591  ·  LineupUI.cpp:2726
（而同类的 LineupUI.cpp:1977 却是 `this->m_OutFrameR.m_disablepic->IsLoaded` ✓ 有前缀 ⇒ 时有时无 = 缺陷签名 ✓）
```

**根因（已定位 ✓）**：owner 链正则**只认 `\w` 与 `->`** ✗，不认 `.` 与 `[...]`：

```python
r'(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*->\s*(\w+)'      # 8 处同款，其中 2 处在 AST 层（决定真正发射的 owner）
```

且正则**无锚点** ✗ ⇒ 对 `this->A[2].B[0].pDebugTex->__vftable` 会**从 `pDebugTex` 处起匹配** ✗
⇒ owner 被截断成 `pDebugTex` ✗（对照单测 ✓：旧=`pDebugTex`，新=完整链 ✓）。

## 坑：修了它，反而**净增 17 条 C2660**

**两次独立实验，同一结果** ✗：

| 尝试 | 改动位置 | 结果 |
|---|---|---|
| 1 | **legacy 层**（`stage3_cleanup.py:1078/1110/1138` 等四处的 owner 模式） | 总错误 **2150 → 2167** ✗（真新增 **C2660×15** ✗）|
| 2 | **AST 层**（`:476` / `:500` 两处，**只改 owner 提取** ✓） | 总错误 **2150 → 2167** ✗（**C2660×10** ✗；C2065 只从 100→96 ✓）|

**机制** ✓：**owner 文本不只是文本** ✗ —— 它同时是另两条不变式的输入：

1. `_drop_self_arg(args, obj)`（`:610` 附近）用 **owner 文本**判断哪个实参是"self" ✓
 ⇒ owner 变完整后，**self 实参终于被正确丢弃** ✓；
2. 而 **stub 形参表的约定是"对象指针放首位"** ✓（`:494` 注释原文 ✓）
 ⇒ **调用参数少了一个** ⇒ **C2660（参数个数错）** ✗。

⇒ **三条不变式互锁**：①owner 提取 ②self 实参丢弃 ③stub 签名约定 —— **只改一条必然打破平衡** ✓。

## 规则

- **改一个"被别处当输入"的字符串/表达式前，先找它的全部消费者** ✓
 （本例：owner 既进输出 ✓ 又进 `_drop_self_arg` ✓ 还与 stub 签名约定耦合 ✓）。
- **一次只改"决定集合"的那一层，或只改"决定文本"的那一层，二者不可混** ✗：
 ① AST 层（`:578` `_resolve_vftable_calls_ast`）决定**哪些调用被解析** ✓；
 ② legacy 正则层（`:1073-1200`）同样决定**匹配与否** ✗ ⇒ 动它 = 动解析集合 ⇒ 必然与 AST 层重叠 ✓。
- **当"局部修"净亏时，正确动作是回退 + 立为独立项目** ✓，并在规格里写清三条不变式必须**同时**统一 ✓。
- 与 [[page:gotcha-annotation-authored-names-are-claims-not-evidence]] 同族：**先问"这个值还被谁消费"** ✓。
