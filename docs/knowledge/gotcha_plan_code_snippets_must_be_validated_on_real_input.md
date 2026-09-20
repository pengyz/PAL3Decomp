---
name: gotcha-plan-code-snippets-must-be-validated-on-real-input
description: 计划/设计文档里的代码片段若只对着"自造的、简化过的 fixture"写，就会在真实输入上大面积失效——本仓实测：一个 40 行的抽取器计划里有 6 个 bug（2 个致命），全部源于 fixture 不具代表性
type: gotcha
created: 2026-09-20
updated: 2026-09-20
status: active
sources: [session-2026-09-20, data/status/_spike_element_sizes_20260920.md]
---

# gotcha：计划的代码片段必须在**真实输入**上验证过

## 实例（2026-09-20，`??_L/??_M` 站点抽取器）

计划 `docs/specs/2026-09-20-evidence-layer-spike-plan.md` 的"任务 2"给出了完整实现与完整测试。
按它逐字实现后，在**真实 asm**（`original/PAL3.exe.asm`，466 个站点）上暴露 **6 个 bug**，其中 2 个致命：

| # | 缺陷 | 只在真实输入上才暴露的原因 |
|---|---|---|
| 1 | **元组取反**（把源码 push 顺序当实参序）| fixture 的 5 个 push 恰好"看起来"顺序一致；x86 cdecl **右→左**压栈 ⇒ 最后 push 才是 `ptr` ⇒ `size` 会取成 **ctor 地址** |
| 2 | **`_PUSH` 用 `\s*$` 锚定** | 真实 asm 有 **16601 行** `push ... ; comment` 尾注 ⇒ 锚点全失配 ⇒ 站点大面积 incomplete + 43 条"完整但值全错" |
| 3 | `_val` 对 `h` 结尾的符号名直接 `int(...,16)` | 真实 asm 行 8679 `push offset aWidth` ⇒ **`ValueError` 崩溃**（"aWidth" 以 h 结尾）|
| 4 | hex 字面量返回字符串 | 与接口 `size:int`、下游 `binary_size` 比较不相容 |
| 5 | 操作数用 `\w+` | 丢改编符号（`??1stdiobuf@@UAE@XZ_2`）⇒ 6 个假 incomplete |
| 6 | **SEH funclet 归属** | `; START OF FUNCTION CHUNK FOR X` 里的站点**没有自身 `proc near`** ⇒ 被挂到文件里最后一个 proc 名（**213/466，45.7% 全错**）|

## 为什么 fixture 骗过了它

自造 fixture 是**手写的、干净的、无注释的**：
- 没有 `; comment` 尾注（真实 asm 有 16601 行）
- 没有改编符号、没有寄存器/内存操作数、没有 funclet
- push 顺序按"文档里的语义顺序"写 ⇒ **掩盖了取序错误**

## 规则

1. **凡在计划/设计文档里写代码片段，必须至少在一份"真实形态"的输入上跑过** ✓
   （真实输入的标志：含注释尾注、含符号名/寄存器操作数、含边界与异常形态 ✓）
2. **测试 fixture 应直接内联真实输入的行**（本项目做法：把 asm 的 11956-11962 / 47085-47092 等真实行贴进用例 ✓）
3. **测试要覆盖"会翻车的那一类形态"**，而不是只覆盖"能通过的那一类" ✓
   （评审者的检验法：把实现按计划原样写一遍，在真实输入上跑 ⇒ 计划 bug 会当场现形 ✓）
4. **子代理/评审者的"以计划自身测试复算"是有效的检出手段** ✓ —— 本次 6 个 bug 全部是这么找出来的 ✓
