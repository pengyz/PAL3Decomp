---
name: gotcha-attribution-signal-limits
description: 「某函数属于哪个类」的各取证信号及其真实覆盖——mangled 名可靠但覆盖低，函数名本身不可信，operator new 的 size 只能收窄候选
type: gotcha
created: 2026-09-15
updated: 2026-09-15
status: active
sources: [session-2026-09-15]
---

**现象**：`C2039 "'__vftable' : is not a member"` 族（**718 条 / 38 文件**）与 F2 缺口
（118 个含 `__vftable` 的类里 **57 个**无 `vtables` 记录）的共同瓶颈是
**"某个函数属于哪个类"无法证明**。而**现有信号覆盖都不够**，且**有一个信号本身不可信**。

## 关键事实一：**IDA / 注解里的函数名不可信**（这是最反直觉的一条）

实例（均有反汇编证据）：
```
0x4D3280 (58B)  注解名为 ?GetEditorTaskDescription@CEffShock@@QAEPBDH@Z（const char*(int)）
                实为**构造函数**：初始化成员 + 写 3 个 vptr + ret
0x4D3910 (27B)  注解名为 ctor（??0CEffShock），实为**工厂/分配函数**（push size; call new; jmp）
0x4D3860        被名为 CEffQuake::_sdtor，实为 CEffShock 的
0x4C0620 (32B)  被名为 RenderTarget2::scalar_deleting_dtor，但它写的是 CEffObj 的表
0x4D3300 / 0x4C1660 等一批 **145 字节的同形函数**，名字是 ?ExecutePasses@RenderTarget2 /
                ?DestroyEffBase@RenderTarget2 …，实为**内联了 CEffObj ctor 的派生类 ctor**
```
**⇒ 任何"按函数名做归属/做边界判据"的方法都是循环依赖**（用不可靠的名字去修不可靠的名字）。

## 关键事实二：各信号的真实覆盖（实测）

| 信号 | 覆盖 | 判定 |
|---|---|---|
| **mangled 名提类**（`?m@Cls@@` / `??0Cls@@` / `??_GCls@@`）| **108 个类** / 378 处 vptr 站点 | ✅ 可靠（**编译器产物**），但 **F2 缺口 57 类只命中 3** |
| **写表签名**（该函数写入的 vtable 地址集合）| **38 种签名** / 46 个写 ≥3 表的函数 | ✅ **有区分力**（可判"是不是 ctor"与"是否同类"），但**不能单独给出类名**（需锚）|
| **IDA 函数边界** | 5554 个函数 | ✅ **可靠**（抽样 60/60 结尾正常）|
| **`operator new` 的 size** | 见下 | ⚠️ **只能收窄候选** |
| `ida_funcs.get_prev_func` 做归属 | — | ❌ 父函数可能距目标很远、中间隔着别的函数 |
| `decomp` 的 `(address, size_bytes)` 区间归属 | — | ❌ 边界不可靠（`CCBItemWindow` 的 `decomp.address=0x4461B0` **高于**其 vptr 存储 `0x446175`）|
| 计分法（表的最多槽位归属类）| 20/467 表 | ❌ **循环依赖**（需"该类的已知函数 VA"，而缺口类恰恰 `methods=0`）|

## 关键事实三：`operator new` 已确证，但 size 不唯一

```
operator new = 0x55353B
形态：push $size; call 0x55353b   （独立验证：覆盖 74 个 size，且匹配已知类的 binary_size）
实例：CEffShock 的工厂 0x4D3910: push $0x10B0 (=4272=CEffShock.binary_size); call 0x55353b; jmp 0x4D3870
```
⚠️ **`0x541D10` 不是 `new` 而是释放函数**（出现在 deleting dtor 里：`push %esi; call; add $4,%esp`）。
⚠️ **同一 size 对应多个类**（`size=12` → `OpenFNWindow`/`TimeCtl`/`D3DXVECTOR3`/`UIPar_TimeCtrl`）
⇒ **size 只能收窄候选，不能唯一确定类**；需与"工厂跳转到的 ctor"联合使用。

## 关键事实四：F2 缺口的 57 类**不是同一种问题**

| 组 | 数量 | 特征 | 应对 |
|---|---|---|---|
| **A** | **44** | `methods=0` 且 **IDA 无该类函数** | **ctor 被内联进派生类** ⇒ **不存在独立 ctor 函数**；应从**表槽位**反推虚方法集合，**不是去找 ctor** |
| **C** | **7** | `methods>0` 且 IDA **有**该类函数 | ✅ **可直接取证**（`CEffShock`/`ScriptVM`/`NPC`/`CEffQuad`/`CEffExplosive`/`gbRefObject`/`PalScriptWaitObj`）|
| **D** | **6** | `methods=0` 但 IDA **有**该类函数 | **有函数无名** ⇒ 可从函数体取证 |

## 何时使用 / 操作规程

- **先判断目标类属于 A/C/D 哪一组**（决定方法完全不同），**不要一律套同一套流程**。
- **优先用 mangled 名**（编译器产物、可靠）；**不要用注解/IDA 的 demangled 名做判据**。
- 报"某函数属于某类"前，**必须给出 A 级证据**（`reg+disp32`/绝对地址 + 反汇编片段），
  不能只凭名字。
- A 组（44 个）**不要去找 ctor**——它被内联、不存在；走
  `pattern_recover_polymorphic_base_virtual_methods` 的表槽位反推。