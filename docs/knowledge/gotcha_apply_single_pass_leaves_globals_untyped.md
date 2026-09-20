---
name: gotcha-apply-single-pass-leaves-globals-untyped
description: init --force 后只跑一次 apply，全局变量的名字与类型都没落地（0xC10968 仍是 unk_C10968 / 1 字节）——必须再 apply 一次；否则 codegen 出 unk_C10968 而 globals.h 出 g_palScript，报 undeclared identifier
type: gotcha
created: 2026-09-19
updated: 2026-09-19
status: active
sources: [session-2026-09-19]
---

**现象**：`init --force` → `export` → `codegen all` → `probe` 一条链跑完得 S2 **67/201**（总错误 2486，L1 20，
globals 2182/2151）；在同一 IDB 上**只再跑一次 `python pipeline/cli.py apply`** 后重跑同一条链，
同样的源码变成 S2 **70/201**（总错误 2474，L1 21，globals **2753/2696**，+571）。
典型报错形态：`'unk_C10968' : undeclared identifier` —— `Scene.cpp` 里是
`unk_C10968.PalScript::RenderUI()`，而 `globals.h` 声明的是 `extern PalScript g_palScript; // 0xc10968`
（codegen 会用 `data/annotations/globals.json` 覆盖导出名单里的名字，但**改不了已生成的 decomp 文本**）。

**为什么**：`apply_annotations.py` 在**全新 IDB** 上单趟走不完"造 item → 挂类型 → 命名"的依赖链：
`[2] Globals` 的命名发生在 struct/item 尚未建立时，`[6b3]` 只补**名字**、不补**类型**。
在 IDB 副本上用 IDAPython 实测（`ida_name.get_name` + `ida_bytes.get_item_size`）：

| | 名字 | item size |
|---|---|---|
| 第一趟 apply 后 | `unk_C10968` | **1** |
| 第二趟 apply 后 | `g_palScript` | **2176**（整个 PalScript 实例） |

⇒ **长寿命的工作 IDB（多会话反复 apply）天然比 `init --force` 重建的 IDB 更"正确"**，
这就是发布基线（69/202 · L1 18）用干净重建复现不出来的原因 —— 不是 IDA 版本，也不是"脏 IDB 侥幸顶住"。

**何时使用**：
* 跑完 `init --force` **必须再 apply 一次**才算初始化完成（`init --force` 内部只做一趟）。
* 遇到"基线不可复现 / 改完读数反而变差"时，先在 **IDB 副本**上探 name+size 再归因：
  `idat -A -S<probe.py> <副本>`（`probe.py` 只需 `ida_name.get_name` / `ida_bytes.get_item_size`），
  判据是 `0xC10968` 的 size 应为 2176 而非 1。
* 与 `gotcha_apply_silent_fail_idb_lock.md` 的区别：那条是 IDB 被锁导致的**假成功**；
  这条是**真成功但只走了一趟**。两者的排查入口相同（`apply_annotations_log.txt` + item 级探测）。

### 2026-09-19 追加：**"两趟"也不是不动点；构建产物依赖 IDB 历史**

同一天做"全部改动 + 干净重建"验证时又踩到一层：

| IDB 来源 | globals.h/cpp | S2 | matched | L1 |
|---|---|---|---|---|
| `init --force`（内含 2 趟） | 2743 / 2686 | **70/201** | 222/256 | 21 |
| 上者 + 第 3 趟 `apply` | **2746 / 2689** | **70/201** | **222/256** | 21 |
| 长寿命 IDB（同一份注解，累计约 8 趟 apply） | 2746 / 2689 | **71/201** | **225/259** | 21 |

* 第 3 趟把 **globals 追平**（2743→2746），但 **S2 与 matched 没追平** ⇒ 差异不只是"趟数"。
* 逐文件对比定位到唯一的翻转：**`pal3/src/Effect/ScreenEffect.cpp`** —— 在长寿命 IDB 上 ok，
  在干净重建（含 3 趟）上 fail；**注解完全相同、单元数都是 201**。

⇒ **结论（重要）**：`pal3/src` 的通过集**不是注解树的纯函数**，它依赖 IDB 的构建**历史**。
所以"干净重建 + N 趟 apply"**不能**当作长寿命 IDB 的等价替代；任何 A/B 与基线声明都必须
**在同一 IDB 谱系内**比较，跨谱系（干净重建 vs 长寿命）出现 ±1 文件是常态。

**推论（对验证清单的影响）**：用 `init --force` 复算历史读数时，`new_failures`/L1 的"零回退"
判定要在**同一条腿内部**做（改前/改后同谱系），不要拿干净重建的读数去否定长寿命 IDB 上的结论，
反之亦然。

### 2026-09-19 第二轮追加：**趟数与 export 的交替才是关键，且仍开放**

进一步实验（都以 `init --force` 为起点、同一份注解）：

| 做法 | S2 | matched |
|---|---|---|
| `init --force`（2 趟） | 70/201 | 222/256 |
| `init` + 第 3 趟 apply | 70/201 | 222/256 |
| `init` 内跑满 **5 趟 apply**（跑了一版临时实现） | 70/201 | 222/256 |
| `init` 内跑满 **5 对 (apply + fix_vtable_types)** | 70/201 | 222/256 |
| **历史式交替**：`apply → export → codegen → probe` 反复多轮后的同一个 IDB | **71/201** | **225/259** |

* 用 `[6b3] Global names (re)applied` 当收敛判据**已证伪**：它在 217 处持平（217→217），
  而之后的轮次仍在改进读数 ⇒ 别拿它做停下条件。
* 把"趟数"加到 5、或把 `fix_vtable_types` 也配成对，**都没能**复现 71/201 ⇒
  收敛驱动**不是单纯的 apply 趟数**；下一步应查 **`export` 是否也会改 IDB**
  （`export_full.py` 跑 Hex-Rays 时可能落类型/条目），即"apply 与 export 交替"才是收敛路径。
* 因此**目前只保留"两趟"这条已被验证的最小修复**（本会话给 `cli.py init` 加的那条）；
  "5 趟"与"成对跑"两版临时实现**都已回退**（未验证的改动不留）。该问题标记为**开放**。

### 2026-09-19 第三轮追加：**"export 会改 IDB"也被否掉**，剩下最可能的解释是"不同注解版本的序列"

单跑一次 `export`（不做 apply）前后对比：

| 量 | export 前 | export 后 |
|---|---|---|
| `ida_structs.json` 顶层条目 | 1031 | **1031**（不变） |
| `original/PAL3.exe.i64` 字节数 | 86659336 | **86659336**（逐字节同大小） |

⇒ **一次 export 没有新增类型、也没有改变 IDB 规模**，"export 也在改 IDB"这一假设**不成立**（至少不是通过类型增长）。

**至此被证伪的收敛假设**：① apply 趟数（3/5 趟）；② apply+fix_vtable 成对跑 5 次；
③ `[6b3] renames` 作收敛判据（217 处持平）；④ export 单跑新增类型。

**剩下的最可能解释**（供下一轮验证）：长寿命 IDB 是**在注解不断变化的过程中被反复 apply** 出来的
—— 每轮落盘都改了注解，再在其上 apply；而"从最终注解状态反复 apply"无法复现那种**版本序列留下的残留**
（例如某成员先在某类、后被搬到另一类，IDB 里会留下前一轮的条目）。
验法：从干净 IDB 出发，按"改动前注解 → 改动后注解"的顺序分两步 apply，看是否复现 71/201。


