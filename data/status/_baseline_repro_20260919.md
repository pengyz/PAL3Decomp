# 本地基线复现实验（2026-09-19，HEAD = d341ed42b）

> **结论（已定谳）**：发布基线（69/202 · 2446 err · L1 18）**复现不出来，而且不应该被复现** ——
> 它来自一个"多会话反复 apply"的长寿命工作 IDB，而不是 HEAD 决定的可复现态。
> 可复现的 HEAD 态是 **S2 70/201 · 2474 err · L1 21 · matched 222/256**，
> 而且已经收敛成**一条命令**：修好的 `python pipeline/cli.py init --force`。
>
> **根因**：`init --force` 原先在全新 IDB 上**只跑一趟 apply**，而单趟走不完
> "造 item → 挂类型 → 命名"的依赖链。已修（见 §4），并已在 IDB 上验证。

## 0. 纪律声明

* 本轮**只测量**，未改任何 annotation。
* `match` 会推进共享棘轮 `data/status/s4_baseline.json`（并重写 `pal3_registry.jsonl`）；
  因本机读数是 IDA 9.2 环境值、与发布值不同，**每次都 `git checkout` 还原**，不单机推进共享基线。
* `probe` 在本轮统一用 `python pipeline/probe_compile.py all`（只出 census）
  + `tools/regression_detector.py --check`（只读对账），避免顺手刷新 `baselines/latest.json`。

## 1. 四次读数

| # | 状态 | S1 | S2 ok/total | 总错误 | matched | **L1** | globals.h / cpp |
|---|------|----|-------------|--------|---------|--------|-----------------|
| 0 | **发布基线** `baselines/latest.json`（09-19T00:05:52；s4 由 ac686e213 提交） | 751 ok 731 | **69/202** | **2446** | 228/262 | **18** | — |
| A | 长寿命 IDB（09-15 的工作 IDB + 今晚 `apply`） | 730/751 | **70/201** | 2474 | 222/256 | 21 | 2753 / 2696 |
| B | `init --force`（**旧 cli.py：单趟 apply**） | 730/751 | **67/201** | 2486 | 206/238 | 20 | 2182 / 2151 |
| C | `init --force` 旧版 + **手工再 apply 一次** | 730/751 | **70/201** | 2474 | 222/256 | 21 | 2753 / 2696 |
| D | **修复后的 `init --force`**（单条命令，实测末次） | 730/751 | **70/201** | 2456 | 222/256 | 21 | 2743 / 2686 |

**C ≡ A（四个指标逐项相同）** ⇒ 长寿命 IDB 并不"更脏"，它只是**多走了几趟 apply**。
**D 与 C 的头部指标完全相同**（S2 70/201 · L1 21 · matched 222/256 · 失败 131 · partial 173 · unmatched 34），
只有 globals 少 10 个、总错误 2474→2456（−18，属 `gotcha_error_census_not_a_pure_function_of_the_tree`
记录的噪声量级：C1003 截断 + 错误此消彼长）。差异来源：手工那次是 `cli.py apply`（= apply + fix_vtable_types），
而修复后的第二趟只重跑 apply_annotations（fix_vtable_types 仍在 step 5 跑一次）。**留作待查小项。**

失败文件分类：A/C 131 个（annotation_fix 54 · codegen_fix 25 · hexrays_limit 43 · manual_idb 2 · unknown 7）；
B 134 个（56 · 21 · 45 · 2 · 10）。

## 2. 复现配方（一条链）

```powershell
# 前置：本机控制台是 GBK，工具会打印 emoji/CJK
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$env:PYTHONIOENCODING='utf-8'; $env:PYTHONUTF8='1'

python pipeline/cli.py init --force     # 已修：内含两趟 apply（旧版只有一趟）
python pipeline/cli.py export
python pipeline/cli.py codegen all
python pipeline/probe_compile.py all    # 或 cli.py probe all（会顺带对账/刷新基线）
python tools/error_classifier.py --summary
python pipeline/cli.py match            # 注意：会推进共享 L1 棘轮
```

## 3. 与发布基线**残留**的差异（C vs 发布，都是真实差异，不是环境噪声）

* **单元数 201 vs 202**：`pal3/src/Misc/CG_Entry.cpp` 本机**不生成**
  （`CG_Entry.h` S1 直接 `C2059: syntax error : '['`，同时 blocks 4 个 cpp）。
* **新失败 3**：`UIProgressBar.cpp`、`UIStatic.cpp`、`ScreenEffect.cpp`；
  **已修复 4**：`CCBProtectWindow.cpp`、`Combat.cpp`、`UICaption.cpp`、`UIMap.cpp`。
* 两个新失败同形态：``'__vftable' : is not a member of 'UIWnd'`` ——
  生成头里 offset 0 是 `char _gap_000[4]`（`emit_headers` 只发射 `data_members`，丢弃 `__vftable`），
  而 `.cpp` 里仍留**未重写的裸 `X->__vftable->Method(args)`**（60 个 .cpp 含 `__vftable`）。
  `stage3_cleanup.py` 的 t7/fold 覆盖"值/取址"与部分限定链，
  `m_pfather->__vftable->OnMessage(1013, ...)` 这类 thiscall 形态落进空档。
  **这是 HEAD 上真实存在的 codegen 缺口，与 IDB 无关。**

## 4. 根因定谳与修复

**现象**：旧 `init --force` 后 `Scene.cpp` 里是 `unk_C10968.PalScript::RenderUI()`，
而 `globals.h` 声明 `extern PalScript g_palScript; // 0xc10968`
（codegen 用 `data/annotations/globals.json` 覆盖名单里的名字，但改不了已生成的 decomp 文本）
⇒ `'unk_C10968' : undeclared identifier`。

**机制**（在 IDB 副本上用 IDAPython 探测，`ida_name.get_name` + `ida_bytes.get_item_size`）：

| IDB 状态 | `0xC10968` 名字 | item size |
|---|---|---|
| 旧版 `init --force` 之后 | `unk_C10968` | **1** |
| 再 apply 一次之后 | `g_palScript` | **2176**（整个 PalScript 实例） |

⇒ `apply_annotations.py` 在**全新 IDB** 上单趟走不完依赖链：`[2] Globals` 命名时 struct/item 尚未建立，
`[6b3]` 只补**名字**、不补**类型**。

**修复**：`pipeline/cli.py::cmd_init` 在 `[4/4] apply` 之后增加 `[4b/4]` **第二趟 apply**
（并把它的返回值纳入 "INIT INCOMPLETE" 判定）。已在同一台机上验证：
修复后单跑 `init --force`，IDB 副本立刻是 `g_palScript / size 2176`。
知识库条目：`docs/knowledge/gotcha_apply_single_pass_leaves_globals_untyped.md`。

## 5. 本轮顺带修掉的工具缺陷

* **已修**：`pipeline/snapshots/snapshot.py` —— `codegen all` 末尾的 snapshot 在 Windows 必崩：
  `git log --format=%s` 用 `text=True` 走 locale(GBK) 解码 UTF-8 中文标题 →
  ReaderThread 抛 `UnicodeDecodeError` → `.stdout is None`；随后 `write_text` 又用 GBK 撞 U+FFFD。
  已给 3 处 `subprocess.run` + 7 处 `write_text`（另 6 处 `read_text`）显式加
  `encoding='utf-8', errors='replace'`。
* **未修（本轮用环境变量绕过）**：`tools/compile_regression.py:92` 打印 `⚠️` 在 GBK 控制台抛
  `UnicodeEncodeError`，使该步骤"看起来失败"。同类风险：任何打印 emoji/CJK 的 `tools/*.py`。

## 6. 下一步

1. **把 C（70/201 · L1 21）确立为本地基线并显式推进共享文件**
   （`regression_detector.py --save-baseline` + `match`），提交信息注明
   "本机 IDA 9.2 读数"。**需人确认**——共享基线目前保持发布值不动。
2. 修 `__vftable` 的 codegen 缺口（§3 最后一条）：把裸 `X->__vftable->M(args)` 也纳入 t7/fold，
   预计消掉 3 个新失败中的 2 个、并影响 60 个含 `__vftable` 的 .cpp。
3. 之后才回到 `data/status/_cleanup_vtable_class_reconcile.md` §49.4
   （尺寸可疑 9 条 / 归属错 11 条）——基线现在可信了，可以开始落盘。

## 9. 第 15 轮追加（重要）：**构建产物依赖 IDB 历史，不是注解树的纯函数**

在累计落盘 10 条改动（尺寸 2 + 归属 6 + 签名 2）之后，做了一次"全部改动 + `init --force`"的
干净重建验证，结果与逐条验证时用的长寿命 IDB 状态**不一致**：

| IDB 来源 | globals.h/cpp | S2 | matched | L1 |
|---|---|---|---|---|
| `init --force`（内含 2 趟 apply）+ 全部改动 | 2743 / 2686 | **70/201** | 222/256 | 21 |
| 上者再跑第 3 趟 `apply` | 2746 / 2689 | 70/201 | 222/256 | 21 |
| 长寿命 IDB（**同一份注解**，累计约 8 趟 apply） | 2746 / 2689 | **71/201** | **225/259** | 21 |

* 第 3 趟把 globals 追平（2743→2746），但 **S2 与 matched 没追平** ⇒ 差异不只是"趟数"。
* 逐文件对比定位到唯一翻转：**`pal3/src/Effect/ScreenEffect.cpp`**（长寿命 IDB 上 ok、干净重建上 fail，
  注解完全相同、单元数都是 201）。

**据此修正本会话早前的两处说法**（如实记账）：
1. 第 8 轮报的"S2 70→71、matched 222→225"是**长寿命 IDB 谱系内**的读数；在干净重建谱系里
   它是 **70/201、222/256** —— 那 +1 文件 / +3 符号**不能**由 `init --force` 复现。
2. 因此**本地可复现基线应写 70/201 · 222/256**（§1 的 D 行），而 71/201 只能标为
   "长寿命 IDB 谱系读数"。L1 **21** 在两条谱系里一致，仍然可信。

**对验证清单的影响**：`new_failures`/L1 的"无回退"判定必须在**同一条腿内部**做（改前/改后同谱系）；
不要用干净重建的读数去否定长寿命 IDB 上的结论，反之亦然。已同步写入
`docs/knowledge/gotcha_apply_single_pass_leaves_globals_untyped.md`。

## 10. 第 16 轮：把"依赖 IDB 历史"落到**具体机制**上

`ScreenEffect.cpp` 在干净谱系里只差 **1 条**错误：

```
L59 C2664 'sub_4B59B0' : cannot convert parameter 1 from 'char *' to 'float *'
```

而生成源码 L59 是：

```cpp
case 9:
  sub_4B59B0((char *)this, (int)v4, v3, (int)v6, (__int64)v5);
  break;
```

对照组：紧邻的 `case 8` 调兄弟函数 `sub_4B5BB0((float *)this, ...)`，类型是 `float *`。

**机制**（已核实）：
1. **`0x004B59B0` 在任何注解文件里都不存在**（搜遍 `data/annotations/**` 为空）⇒ 它的签名**完全来自 IDA 自己的类型推断**；
2. 同一张调用点（来自 `ScreenEffect` 某函数的 decomp）与**声明**（来自被调函数自己的 decomp/导出）**各自独立推断**，
   只要两边不一致就会得到 `C2664`；
3. 长寿命 IDB 里两边已收敛（都成了 `char *` ⇒ 通过），干净重建里推断成 `float *` ⇒ 一条错误。
   顺带说明 `sub_4B59B0` 本体是 `mov esi, ecx`（**用 ecx 当 this**）并取 4 个栈参 ⇒ 它其实是个
   thiscall 形态的函数，只是**没有注解**，于是身份由 IDB 猜。

**⇒ 这才是"构建依赖 IDB 历史"的最小可复现实例**：**未注解的 `sub_` 函数签名是 IDB 推断值**，
它在不同 IDB 谱系间可以不同，进而让调用点/声明不匹配。

**两条候选修法**（都需单独做并验证，本轮**不动手**）：
* (a) **注解 `0x004B59B0`**：把它固定下来（先用 asm 取真实参数类型与返回类型 —— 本体用 `ecx` 作 this、
  4 个栈参、首参是对象指针）；同类还有一批 `sub_`（`sub_4B5570`/`sub_4B5830`/`sub_4B5BB0` 等，见 §3 的新失败清单）。
* (b) **codegen 侧**：让同一 `sub_` 被多次推断出不同签名时**合并/告警**，而不是各自发射声明 ——
  这属于"同一符号多份声明"的缺陷类，和 MEMORY 里 `globals.cpp` 同名去重那段同型。

## 11. 第 17 轮：清点 `sub_4B59B0` 的可修性（结论：**不能靠单条注解修，需专门一轮**）

| 事实 | 值 |
|---|---|
| 全仓调用点 | **只有 1 处**：`pal3/src/Effect/ScreenEffect.cpp:59` → `sub_4B59B0((char *)this, (int)v4, v3, (int)v6, (__int64)v5);` |
| 注解 | **完全没有**（`data/annotations/**` 里搜不到 `0x004B59B0`） |
| 本体形态 | `mov esi, ecx`（**ecx 当 this**）+ 栈参 `arg_0/arg_4/arg_8/arg_C`（**4 个 dword**） |
| 调用点实参 | 6 个 dword（`this` + v4 + v3 + v6 + `__int64 v5`） |

⇒ 调用点实参个数与本体栈参**对不上**：这不是"注解写错了"，而是**调用点本身是错的**
（Hex-Rays 对该被调函数的建模与本体不符）。所以"给 `0x004B59B0` 补一条注解"**不足以**修好它，
需要先判定真身（`ecx` 当 this ⇒ 大概率是个 `__thiscall` 成员函数、其"首参"其实是 `this`）再决定：
是补注解，还是让 codegen 在"同一符号多签名"时收敛/告警。**本轮不动手**。

---

## 12. 交给下一轮的**优先级队列**（带证据与预期收益）

按"投入产出 + 风险"排序，每一项都写清了判据与验证方式：

1. **codegen：补 `__vftable` 裸链缺口**（预期收益最高，且是纯 codegen 改动）
   * 现象：生成头里 offset0 发射成 `char _gap_000[4]`（`emit_headers` 只发射 `data_members`），
     而 **60 个 .cpp** 里仍留有**未重写的裸 `X->__vftable->Method(args)`**；
     t7/fold（`pipeline/gen/stages/stage3_cleanup.py`）覆盖了"值/取址"与部分限定链，
     `m_pfather->__vftable->OnMessage(1013, …)` 这类 thiscall 形态落空。
   * 已知代价：`UIProgressBar.cpp`、`UIStatic.cpp` 两个文件因它失败（`'__vftable' : is not a member of 'UIWnd'`）。
   * 验证：`new_failures` 必须为 0、L1 不得回退；预计消掉干净谱系 6 个新失败中的 2 个。
   * **第 18 轮精确量化（这一项现在是 turnkey 的）**：
     * 非注释行含 `__vftable` 的共 **150 行 / 29 个 .cpp**；其中**真正未重写的裸链只有 11 行**，
       而且只调**两个方法**：`OnMessage` ×9、`ShowWindow` ×2。
     * 分布：`UIProgressBar.cpp`（4）、`UIStatic.cpp`（4+）、`UIListBox.cpp`、`CCBRoleState.cpp`（2）。
     * **`ShowWindow` 已在 `UIWnd` 的注解方法表里** ⇒ 这 2 处（`CCBRoleState.cpp`）只需把裸链重写成
       `obj->ShowWindow(x)` 即可编译。
     * **`OnMessage` 不在 `UIWnd` 的方法表里，但它确实是 UIWnd 的 vtable 槽**：槽地址
       **`0x00445D10`**（在 UIWnd 三张表 `0x56AE2C`/`0x56AFB0`/`0x56AEC8` 里都是第 7 槽）**同时被注解为
       `OnMessage`**（与 12 个类的 `OnMessage` 实现之一吻合）。⇒ 这 9 处应走**已有的 vtable 槽机制**
       （`vtbl_XXXX` typedef + `pal3_vtbl_*` stub，代码里已为 `obj->__vftable + N` 形态实现），
       即"按槽位发射调用"，而**不是**天真地重写成 `obj->OnMessage(...)`（那会报"不是 UIWnd 成员"）。
     * 落地位置：`stage3_cleanup.py` 的 t7/fold（`_fold_vftable_mask`）与
       "Generic OOP substitution"（`obj->__vftable->M(obj, …)` → `obj->M(…)`）两段之间，
       补一条"裸链 + 方法名 → 先查接收者方法表、再查其 vtable 槽"的分支。
   * **第 19 轮补完：这一项是"两部分"改动，必须同时做**（否则只换个错法）：
     * **(i) codegen**：把裸链重写成 `obj->Method(args)`（`ShowWindow` 那 2 处到此即可）。
     * **(ii) annotation**：`OnMessage` 必须**被 UIWnd 的方法表声明** —— 现在 `UIWnd.json` 的方法表里
       **没有** `OnMessage`，于是重写后只会得到"`OnMessage` : is not a member of `UIWnd`"。
       证据（够格落盘）：**槽地址 `0x00445D10` 在 UIWnd 的三张表里都是第 7 槽**（`0x56AE2C`/`0x56AFB0`/`0x56AEC8`），
       且该地址**被注解为 `OnMessage`**；9 个调用点都传 3 个 int（`OnMessage(1013, (int)this->m_id, v17)`）。
       ⇒ 它是 UIWnd 的真虚函数，补一条方法条目即可（名字用 `OnMessage`，签名按调用点定）。
     * **⚠️ 爆炸半径警告**：往 `UIWnd` 加**虚函数**会改变 UIWnd 及其全部派生类的头文件/方法发射顺序
       ⇒ 可能牵动很多文件、甚至碰到 L1。**必须**用 `apply_annotation_batch.py --run-pipeline` + `match`
       一次做完并逐步核对（`new_failures` 必须 0、**L1 不得回退**）；一旦 L1 掉，按纪律回退该条。
     * 预期收益：`UIProgressBar.cpp`、`UIStatic.cpp`、`UIListBox.cpp`（干净谱系 6 个新失败里的 2–3 个）。
   * **第 20 轮修正（这条把上面的爆炸半径风险去掉了，方案定型）**：
     `0x00445D10` 已被 **`CGameData`** 拥有（`OnMessage(int nVal, int nMsg, int wParam)`，
     `int __thiscall`）。所以**不该**把 `OnMessage` 加进 `UIWnd`（那会与 `CGameData` 重复拥有同一地址），
     而应把裸链重写成**本代码库已经在用的"cast + 限定调用"形态**：

     ```cpp
     obj->__vftable->OnMessage(a, b, c)   →   ((CGameData *)obj)->CGameData::OnMessage(a, b, c)
     ```

     **先例充分**：`free_functions.cpp:5798` 就是
     `return (((CGameData *)v1))->CGameData::OnMessage(nVal, (int)nMsg, wParam);`，
     全仓 `CGameData::OnMessage(` 共 **50** 处，另有 `((CGameData *)&g_gamefrm)->CGameData::Load(...)` 等同类。
     `<Owner>` 从"接收者类的 vtable 注解里该槽的归属"取（注解的 slots 已带 `from`/归属信息）。
     ⇒ 这条**不碰任何类模型**（无 UIWnd 虚函数、无派生类波及），只是把发射形态换成既有约定，
     风险与预期收益都回到"一次 codegen 小改 + 全链验证"的量级。**本轮仍未动手**（需一次全链迭代的余量）。

## 13. 第 21 轮：**当前**失败集重算 —— 队列第 1 项的预期收益被精确验证

早前 §3/§12 里那份"6 个新失败"的清单已**过期**（`Scene.cpp`/`SceneMgr.cpp`/`UICamera.cpp` 现在都是 **ok**）。
以当前状态（干净重建 + 3 趟 apply + 全部已落盘改动）对**发布基线**重算：

| | 结果 |
|---|---|
| 新失败 | **3 个**：`Effect/ScreenEffect.cpp`、`Misc/UIProgressBar.cpp`、`Misc/UIStatic.cpp` |
| 已修复 | **4 个** |

逐文件归因（这是本项的**验证过的**预期收益）：

| 新失败文件 | 成因 | 队列第 1 项能否修 |
|---|---|---|
| `Misc/UIProgressBar.cpp` | 裸 `X->__vftable->OnMessage(...)` × **4** | ✅ 能 |
| `Misc/UIStatic.cpp` | 裸 `X->__vftable->OnMessage(...)` × **4** | ✅ 能 |
| `Effect/ScreenEffect.cpp` | `sub_4B59B0` 调用点实参个数与本体不符（**非** `__vftable`） | ❌ 不能（属队列第 4 项） |

⇒ **队列第 1 项做完应把 3 个新失败消掉 2 个**（`UIProgressBar.cpp` + `UIStatic.cpp`），
判据是 `new_failures` 归零、L1 保持 21。这是本会话给出的**最具体、最可检验**的一次预期。
（`UIListBox.cpp`/`CCBRoleState.cpp` 里也有裸链，但它们不在新失败集内 ⇒ 该重写对文件级读数的
影响**上限就是这 2 个文件**，不要期望更多。）

## 14. 第 22 轮：把第 1 项的"接收者类型"问题也解决了 —— 它**就在那一行里**

之前担心"codegen 在 stage3 拿不到接收者的静态类型"。实测 `asm/pal3/decomp/UIProgressBar_CheckRayHitRoleint_int_00439a20.json`
后确认：**类型信息就在失败行本身**，两种形态各有一种：

```c
// 形态 A（裸链，4 处）
m_pfather->__vftable->OnMessage(1013, (int)this->m_id, v17);
v29->__vftable->OnMessage(1017, (int)this->m_id, v27);
v40->__vftable->OnMessage(1014, (int)this->m_id, v37);
v41->__vftable->OnMessage(1015, (int)this->m_id, v37);

// 形态 B（cast 链，2 处）—— **cast 里直接写着接收者类型 `UIWnd *`**
((void (__thiscall *)(UIWnd *, int, void *, int))v24->__vftable->OnMessage)(v24, 1016, this->m_id, 0);
((void (__thiscall *)(UIWnd *, int, void *, int))v34->__vftable->OnMessage)(v34, 1018, this->m_id, 0);
```

⇒ 落地规则（机械、无需新 plumbing）：
1. 识别 `RECV->__vftable->NAME(` 与其 cast 包裹形态 `((...)(RECV->__vftable->NAME))(`；
2. 由 `RECV` 的静态类型名（形态 B 从 cast 直接读；形态 A 从该函数 decomp 里 `RECV` 的声明读）
   查该类的 vtable 注解 → 得到 `NAME` 所在槽的**归属类** `Owner`（本例 `UIWnd` 第 7 槽 `0x00445D10` → **`CGameData`**）；
3. 发射成既有约定形态：**`((Owner *)RECV)->Owner::NAME(<去掉首参 this 后的实参>)`**
   —— 形态 A 本就无首参、形态 B 要把 `RECV` 从实参里去掉（它已变成限定调用的 `this`）。
4. 全链验证：`new_failures` 必须归零（预期 `UIProgressBar.cpp` + `UIStatic.cpp`）、**L1 保持 21**。

**这条现在没有任何未决点**，只差实现与一次验证迭代。

### 14.1 第 27 轮：把"只差实现"再收窄到**一个函数**

读 `stage3_cleanup.py` 后发现：**解析器早就宣称处理"plain `__vftable->Method`"** ——
第 998-1003 行的注释写明 `_resolve_vftable_calls_ast(code, ctx)`（第 1004 行调用）
"handles every syntactic form the tree-sitter parse can see: named-slot cast calls, raw-offset casts,
**plain __vftable->Method**"，且"unresolved calls are rewritten to synthesized signature-accurate stubs"。

它的工作方式（第 577-581 行）：遍历 AST，对**函数子树里含 `__vftable` 的 `call_expression`**
调用 `_decode_vtbl_call(node)`。

⇒ 那 11 处之所以仍留裸链，只可能是 **`_decode_vtbl_call` 对这 9 个 `OnMessage` 站点返回了"未解析"**，
随后落到保留原文本的分支。**下一轮的第一件事就是给 `_decode_vtbl_call` 加一次临时打印**，
看它是在哪一步放弃的（最可能是：`ctx` 里没有"接收者类的槽归属"映射，
而接收者又常是局部量 `v29`/`v40`/`v41`，拿不到静态类型）。这一处一旦看清，
按 §14 的三步规则落地即可（发射 `((Owner *)RECV)->Owner::NAME(...)`，先例 `free_functions.cpp:5798`）。

### 14.2 第 29 轮：给出**确切的放弃点**（读代码得到，无需再打印）

`_decode_vtbl_call`（第 432-479 行）**对命名形态是解析成功的**：

```python
mn = re.search(r'(\w+(?:\s*->\s*\w+)*)\s*->\s*__vftable\s*->\s*(\w+)', text)   # 第 476 行
if mn:
    return {'obj': mn.group(1), 'method': mn.group(2), 'offset': None,
            'cls_hint': cls_hint, 'ret': ret, 'params': params}                # 第 478-479 行
```

即 `{'obj': 'm_pfather', 'method': 'OnMessage', 'cls_hint': …}` 是**能拿到的**。问题在**消费者**（第 581 行之后）。

而 `cls_hint` 的来源只有一处（第 455-473 行）：**函数表达式里的 cast**（`(void (__thiscall *)(UIWnd *, …))…`）。
⇒ **形态 A（裸链 `m_pfather->__vftable->OnMessage(...)`）根本没有 cast，`cls_hint = None`**，
消费者便无法把 `OnMessage` 映射到某个类的声明/槽 ⇒ 落到"保留原文本"分支。

**因此实现只需补一件事**：给形态 A 求出接收者的静态类型。
来源就在同一函数的 decomp 文本里（声明行 `UIWnd *m_pfather; // …`、`UIWnd *v29; // ecx`）——
把"本函数内 `obj` 的声明类型"喂给消费者即可（`ctx` 若已带 locals/params 类型则直接用，否则正则扫函数头声明区）。
拿到类型后按 §14 三步走：查该类 vtable 注解 → 槽归属类 `Owner` → 发射 `((Owner *)obj)->Owner::NAME(...)`。
2. **`CEffMgr` 区段协同改**（证据已齐，但改动面大）
   * `tagEffClass.binary_size: 4 → 72` **有两侧证明**（下界=记录内 +0x44 当指针；上界=32 条记录不越 `m_EffTable`@0x91C；
     `0x1C+32×72=0x91C` 精确吻合）；但跨度 `0x1C..0x91C` 内压着 **20 个**与指令冲突的成员
     （`m_fPosX`@0xA0 被当字节读、`m_fPosZ`@0xA8 被当指针用）⇒ 必须一次改完 20 条并全链验证。
3. **`sub_479260`**（632 步长 + 基址 `+0xC2F80`）与 **`sub_4EC700`/`sub_504130`**
   * 前者的宿主类成员表在该区间为空；后者判定为"`this` 是结构体中间指针 ⇒ 很可能不是成员函数"。
   * 需要的手段：逐访问对象溯源（dataflow）或先补齐宿主类成员模型。
4. **`ScreenEffect` 家族的 `sub_`（`4B5570`/`4B5830`/`4B59B0`/`4B5BB0`）**
   * 见 §11：需先判定真身（`ecx`=this ⇒ 很可能是成员函数）再补注解；补对了可能消掉干净谱系 1–3 个失败。

**贯穿性的提醒**（本会话反复验证）：
* 读数只有一个可信基础：**同一条 IDB 谱系内**改前/改后对比（§9）；跨谱系（干净重建 ↔ 长寿命）出现 ±1 文件是常态。
* 只有"精确命中"可作归属判据；"成员内"会被末成员跨度兜底高估（工具文档已注明）。
* 遇到工具报"0 个偏移"**必须手工读 asm** —— 本会话 3 条定案都是这么来的。
