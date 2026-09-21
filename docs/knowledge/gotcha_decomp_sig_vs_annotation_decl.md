---
name: gotcha-decomp-signature-vs-annotation-declaration-can-disagree
description: 不是"两套模型"而是"同一模型的副本缺归一化"——decomp 侧签名 99.2% 带显式 this（元数虚高 1），且 method_sigs 用裸名 key + setdefault 使重载塌缩（DelTask 2参/3参互相覆盖）⇒ 以它为元数依据的改写会同时误伤调用点与函数定义头
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：签名副本缺归一化（不是"两套模型"）；拿未归一化的那份会把**函数定义头**都改坏

## 现象

要修一族 `C2660`（`'X' : function does not take N parameters`），机制是
**Hex-Rays 把 `__thiscall` 调用建模为"类限定名 + 显式 this 作首实参"**：

```c
CCBControl::SetParam(*(CCBControl **)(... + 8), 513, -1);   // 声明 int SetParam(int, int) = 2 参
NPC::UpdateAnim((NPC *)(v3 + 156304));                      // 声明 void UpdateAnim() = 0 参
```

⇒ 安全闸设计为「**实参数 == 形参数 + 1** 且签名含 `__thiscall`」，形参数取自
`store.method_sigs['Cls::M']`（`pipeline/gen/data.py` 注释：`"ClassName::Method" -> decomp signature`）。

**实测：这个来源是错的** —— 两处**独立**误伤（都用真实站点复现）：

| # | 形态 | 误伤结果 |
|---|---|---|
| ① | `A->Cls::M(explicit_this, args)`（**对象是前缀**）| 改成 `A->((Cls *)explicit_this)->M(args)` ⇒ **双解引用链**；`CCBSystem.cpp` **35 → 102** 条错、总数 2150 → **2242** |
| ② | **函数定义头** `BOOL CCBSystem::CreateObj(CCBUI **ppUI, const char*, UINT)`（3 参）| decomp 侧记 **2** 参 ⇒ `3 == 2+1` 开闸 ⇒ `BOOL ((CCBSystem *)CCBUI **ppUI)->CreateObj(...)` ⇒ `C2199 syntax error : found 'BOOL (' at global scope` + C2143 + C2447 |

补上①的链式守卫（不匹配紧跟 `->`/`.`/`::` 的类限定名）后：**C2660 净变化 = 0**，
总错误 2150 → **2152** ⇒ 发布门禁拦下，改动撤下。

> ⚠️ 注意：带①误伤时的「C2660 −30」是**假象** —— 损坏把一批 C2660 变成了别的错误码。
> 撤下前必须看**总错误**与**逐码净增减**，不能只看目标错误码。

## ⚠️ 更正（2026-09-21 当晚，同一会话内进一步取证）

初版把它写成"**decomp 模型 ≠ 注解模型**（两条独立数据链）" ✗ —— **不准确**。逐字取证后：

| 事实 | 证据 |
|---|---|
| decomp 签名**一律带显式 `this` 形参** | `__thiscall` 签名 **3090/3116 = 99.2%** 首参形如 `Cls *this`（其余 26 条首参名为 `Block`/`parent`/`int this`，**仍是 this 槽**）|
| `method_sigs` **按裸名索引 + first-overload-wins** | `data.py` 装载处注释原文：`index by the bare "Cls::M"; first overload wins (best-effort)`，用 `setdefault` |
| **生成头把 `this` 正确剥掉了** | 注解 `bool __thiscall(CCBStage *this, int nIndex)` → 头 `bool DelTask(int nIndex);` ✓ |
| 于是**两份文本的差异只是"归一化"** | `char *__thiscall(CCBStage *this, int, _BYTE*, int*)` → 头 `char * DelTask(int, _BYTE*, int*)`（3 参）✓ |

**真正的两个缺陷都在 `method_sigs` 这一份副本上**，与"注解模型"无关：

1. **元数虚高 1**：签名含 `this` 槽 ⇒ 文本元数 = 真实形参数 **+ 1**（99.2% 的 `__thiscall`）；
2. **重载塌缩**：裸名 key + `setdefault` ⇒ 同名重载互相覆盖（`CCBStage::DelTask` 的
   1 参与 3 参两个重载只留一个）⇒ 消费者无法知道"有哪些元数"。

⇒ **结论修正**：不是"元数必须取注解声明"，而是"**元数必须取一份已归一化的声明**"——
生成头/头生成器那份是对的，`method_sigs` 那份缺归一化。
⇒ **不要新建平行表**（那会成为**第三份副本**，正是本会话诊断出的病）；
应在**既有 loader 上**补：`__thiscall` 剥首参 + 记录**元数集合**（不覆盖既有 `method_sigs`，避免 3 个既有消费者受影响）。

## **为什么**

* `method_sigs` 来自 **decomp JSON**（Hex-Rays/IDB 当时的原型），
  而编译器读的是**生成头里的注解声明**。两者是**两条独立的数据链**：
  注解在 IDB 里被修正过/更完整（如 `DelTask(int) → DelTask(int, _BYTE*, int*)`），
  decomp JSON 却是更早一次 export 的产物 ⇒ **元数可以差 1 甚至更多** ✗。
* 这正是"**先验证消费者实际读的是哪份声明**"这条纪律的直接应用：
  改写/门禁若以"我以为的那份"为依据，就会在**消费者不看的那份**上做判断。

对照实验（顺带**证伪**一个假设 ✓）：MSVC6 **接受** `p->Cls::M()` ——
`struct A{void M();}; void f(A*p){p->A::M();}` 编译 **0 错误** ⇒
`A->Cls::M(...)` 形态**不需要**任何改写（当时的 C2059 怀疑是错的）。

## **何时使用**

* 写任何**依据形参数**的 codegen 改写/门禁时：**元数必须取自生成头（注解）**，
  不要把 `store.method_sigs` 当权威 ✗；若必须用，则要求**两侧一致**才动手（保守跳过不一致者）。
* 看到 `C2199 syntax error : found '<类型> (' at global scope (was a declaration intended?)`
  配 `C2143`/`C2447`：**几乎必然是某个改写把函数定义头吃掉了** ✓ —— 直接去那行看。
* 评估一个改写是否成功：**只看目标错误码会骗人** ✗ ——
  必须同时看"总错误"与"逐错误码净增减"（`tools/regression_detector.py`），
  因为损坏常把错误码 A 变成错误码 B。
* 代码资产：纯函数 `_sig_arity` / `rewrite_explicit_this_call` / `_fix_explicit_this_calls`
  与 **19 项单测**（`tests/test_explicit_this_call.py`，含上述两类误伤的真实样本）
  已固化在 `pipeline/gen/stages/stage5_fixup.py`，**故意不接线**，待"注解元数"可用后再接。