---
name: gotcha-vtables-not-derivable-from-bytes
description: vtables 无法从二进制导出——表在 .rdata 连续排布且内容全是 .text 指针，字节层无「表结束」信号；IDA 也不为它们建结构
type: gotcha
created: 2026-09-15
updated: 2026-09-15
status: active
sources: [session-2026-09-15]
---

**现象**：想给某个类补 `structs/<Cls>.json` 的 `vtables` 记录时，**无法从二进制得到可信的槽位列表**。
实测 `CEffShock` 的三张表被读出 **24 / 39 / 42 槽**（应远小于此），里面混进了
`RenderTarget2::CalcDeltaTime`、`CEffQuake::AllocSegments` 等**别的类**的函数。

**为什么**（逐条实测，6 个判据全败）：

| 判据 | 结果 |
|---|---|
| RTTI COL（表前一个 DWORD 指向 `.rdata`）| **5/467 = 1%** ⇒ 这些表**没有 COL**（`/GR` 下也未生成）|
| "下一个 ctor 实写地址"作边界 | 多继承连续子表下失效 |
| 槽位**函数类族**一致性 | **根因是函数名本身不可靠**（见 `gotcha_attribution-signal-limits`）⇒ 循环依赖 |
| IDA vftable 注册表 `ida_typeinf.get_vftable_ea(ordinal)` | 序数循环 **0 条** |
| IDA 的 `??_7` 符号 + UDT | IDA 里只有 **8 个** `??_7` 符号、**全部 `no_udt`**，且**都不在** 467 个 ctor 实写地址里；其中 4 个内容全是 `FFFFFFFF`（占位）|
| 连续 `.text` 指针 → 首个非 `.text` | 部分可用（`AStarPathFinder` **3 槽** ✅ 与注解一致；`std::out_of_range` 3 槽 ✅）<br>但 `CEffAction` **96 槽**（注解 15）、`CEffCylinder` **18 槽**（注解 15）⇒ 仍吞并 |

**根因**：这些 vtable 在 `.rdata` 里**连续排布、内容全是 `.text` 指针** ⇒
**字节层不存在"表结束"的信号**。要切开它们必须知道**每个类的虚函数个数**——
**那是编译器的知识，不在二进制的字节里。**

**这解释了 `pipeline/ida/export_full.py:50-52` 的那条注释**：

> `asm/pal3/ida_structs.json` 的 `vtables/methods/_variants` 与注解**逐字段等值**（761/761）
> ⇒ **它们是"注解的复制"，不是 IDB 状态的证据**

**根本原因**：`vtables` 的源头本就是**人的知识**，所以它必然是注解的复制，不可能由 export 推出。

**何时使用 / 操作规程**：
- **不要**试图"从二进制导出 `vtables`"——那是死路（本条目已穷尽 6 个判据）。
- **正确路径**：写 `methods`（虚方法**名 + 地址**，地址是二进制事实、可取证）
  ⇒ `apply` 写入 IDB 的 struct methods ⇒ `codegen` 据此发 `virtual`
  ⇒ **编译器自己合成 vtable**。这条路已实测验证（补 `CEffObj` 虚方法后成功合成
  `??_7CEffCylinder@@6B@`，13 槽、**槽序 = 源码声明序**）。
- **可用的顺序线索**：表被"吞并"影响的是**表尾**，**不影响表头** ⇒
  从 base 顺序读到第一个"确定属于别的类"的槽，即可得到**真实的前段顺序**。
- ⚠️ 注意 `codegen` **两个字段都消费**：`pipeline/gen/data.py:238-256` 用 `vtables` + `methods`
  **两者**构建 `{slot_index: method_name}`（`if not _vtables or not _methods: continue`）；
  `emit_headers.py:662` 则要求 `methods` 非空。⇒ 只补一个不够。