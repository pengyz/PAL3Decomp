# 多类 binary_size 修复 · 单批一次跑通（设计规格）

> 日期：2026-09-21 · 路径：**Architectural** ✓ · 状态：待用户复核
> 上游：`data/status/_d1_ledger.md`（R1–R13）· `tools/ida/forensics_alloc_per_class.py`（IDB V3）

## 0. 问题

本仓有 16 个类**申报的 `binary_size` 与二进制真值不符**。此前即使证据齐备也难以落地，因为
①多文件级联靠人工 ✗ ②派生 UDT 布局过期致 `apply` 越界拒绝 ✗ ③半写风险 ✗ ④陈旧计划 ✗。
本会话已用 `UIStatic 152→248`（60 类 / **L1 34→38** ✓）端到端证明这条路可行 ✓。
本规格把这套机制**一次性**用在**其余已取证**的类上。

## 1. 目标与非目标

**目标**：把**已获 IDB A 级尺寸证据**且**计划自检通过**的类，**合成一个批次**、**一次管线**落地并验收。

**非目标**（明确排除 ✗）：
- **6 个 `self_check=False`** 的类（`CCBUIPanel`/`UIScenePanel`/`CCBRoleState`/`UISceneFrm`/`CCBStageScene`/`UICoverFrm`）：
  其尺寸 IDB 已证 ✓，但**成员会越界** ⇒ 需**成员级取证**后才能落 ⇒ **本规格不包含** ✗。
- 不做"重命名/归属/签名"类修改 ✗；不碰 `data/annotations/functions.json` ✗；不改 IDB ✗（只读查询 ✓）。

## 2. 证据层（唯一尺寸权威）

**判据**：MSVC 的 `new Cls(...)` 惯用法
```
push N ; call ??2@YAPAXI@Z ; … ; call <Cls 的 ctor>
```
⇒ `N` = **该类整对象尺寸**（A 级 ✓），被调的 ctor = **身份**（A 级 ✓）。
**交叉校验**：vtable-store（ctor 首条 `[reg]` 存储 ✓）与 `[reg+imm]` 上界（**仅作参考** ✗，单函数上界不是尺寸 ✓）。

**已取证结果**（IDB V3 实测 ✓）：

| 类 | IDB `push N` | 申报 | 注解 | 级联 | 自检 |
|---|---|---|---|---|---|
| `UITitle_ArcSave` | **4004** ✓ | 4004 | 4196 | 1 | True |
| `CCBUI` | **2632** ✓ | 2632 | 2648 | 1 | True |
| `CScreenMode` | **5496** ✓ | 5496 | 5880 | 1 | True |
| `JusticeBookUI` | **56192** ✓ | 56192 | 58496 | 1 | True |
| `UIRoleSelectDialog` | **2204** ✓ | 2204 | 2300 | 1 | True |
| `UIListBox` | **1760** ✓ | 1760 | 1208 | 13 | True |
| **`ScreenEffectNode`** | **424** ✓ | ~~1060~~ ✗ | 220 | 待测 | 待测 |
| **`UISceneMap`** | **232** ✗ **误归属** | 232 | 1204 | 待测 | 待测 |

⇒ **前 6 个**证据与自检齐备 ✓；**后 2 个**须先补取证（见 §3）。

## 3. 两处待补取证（只读 ✓，前置）

1. **`UISceneMap` 的真实分配点** ✗：V3 把 `push 0xE8(232)` 归给了 `?ctor@UISceneMap@@QAEHXZ`，
   但 232 对该类**不可能**（其成员末端已 1012 ✓）⇒ 该 ctor 名**可能误标** ✓。
   **取证**：查该 ctor 的**首条 `[reg]` 存储目标 vtable** ✓ + 查**所有** `UISceneMap` 相关 `push N` ✓；
   **若无法定谳** ⇒ **从本批剔除** ✓（**不硬凑** ✗）。
2. **`ScreenEffectNode` 424 复核** ✓：已有 `push 424` + ctor `ScreenEffectNode_ScreenEffectNode` ✓；
   **补**：确认无**第二个**更大分配点 ✓，并跑该类的计划自检 ✓。

## 4. 流程（单批一次跑通）

```
① 只读取证（§3）⇒ 证据表落盘 data/status/_size_fix_evidence_<date>.json
② 逐类生成级联计划（cascade_plan）⇒ 合并为一个批 data/status/_size_fix_plan_<date>.json
③ 静态闸：计划自检(真实尺寸 ✓) + from 断言(== 当前注解 ✓) + 环检测 + 对齐 + 拒绝项(内联 dict/_N 变体 ✓)
④ dry-run：必须 **零落盘** ✓
⑤ 两阶段写盘（先全量校验、任一拒绝即整批不写 ✓）
⑥ pipeline/cli.py check：**失败 ⇒ 中止，不进入 apply** ✓
⑦ 一次全链：apply → export → codegen all --skip-probe → probe all → match
⑧ 当场读判据 ⇒ 通过则提交；破线则**先定位**（读 apply_annotations_log.txt ✓）再决定
```

## 5. 涉及文件

- `data/annotations/structs/<类>.json`（§2 的 6 个 + 级联闭包内的持有者 ✓；§3 定谳后可能加 1–2 个）
- `data/status/_size_fix_evidence_<date>.json`（新 ✓ 证据表）
- `data/status/_size_fix_plan_<date>.json`（新 ✓ 计划/批）
- `data/status/baselines/*`、`s4_baseline.json`、`probe_census.json`（门禁产物 ✓）
- 复用既有工具 ✓：`tools/cascade_plan.py` · `tools/apply_annotation_batch.py --dry-run` ·
  `tools/ida/forensics_alloc_per_class.py` · `tools/check_member_extent.py`

## 6. 验收判据（全部必须满足 ✓）

| 判据 | 阈值 | 来源 |
|---|---|---|
| `check` | **exit 0** | `pipeline/cli.py check` |
| `new_failures`（ok→fail）| **0** | probe 对账输出 |
| **L1** | **≥ 38** | `match` 的 ratchet（**当场读** ✓，不可事后查文件 ✗）|
| **S2 ok** | **≥ 79** | `probe` 输出 |
| 总错误 | **≤ 2148** | `probe` 输出 |
| 计划自检 | **True** | `cascade_plan.self_check` |
| `from` 断言 | **0 失配** | 批生成脚本 |
| `ScreenEffectNode` 落地后 | `MemberExtent` **不再报它** ✓ | `check_member_extent` |

## 7. 错误处理与退路

- **静态闸不过** ⇒ 中止且**零写入** ✓（机制已实现 ✓）
- **`apply` 失败** ⇒ **先读 `pipeline/ida/_logs/apply_annotations_log.txt`** ✓（**禁止盲目回退** ✗）
- **落地后退化** ⇒ `/tmp` 整目录备份回退 ✓ + **补跑恢复链** ✓（只回退注解不够 ✗）+ **杀整条进程链** ✓（R12）
- **回退方式**：`cp -f /tmp/<bak>/*.json data/annotations/structs/` ✓ 或 `git show HEAD:<path> > <path>` ✓
  —— **禁止** `git checkout/restore/stash/clean` ✗
- **`UISceneMap` 取证冲突** ⇒ 剔除该类，其余照常 ✓（§3.1）

## 8. 风险

| 风险 | 缓解 |
|---|---|
| 合并批次放大影响面 | 两阶段**全或无** ✓ + `check` 中止 ✓ + dry-run 零落盘 ✓ |
| 级联模型在某类上不成立 | 逐类自检（真实尺寸 ✓）+ 环/对齐闸 ✓；`UIListBox`(13 类) 是最大级联 ✓ |
| 陈旧计划 ✗ | **计划必须落盘** ✓ + `from` 断言 ✓（机制已验证 ✓）|
| 事后误判退化 | L1 棘轮**回写基线** ✗ ⇒ 必须**当场读** ✓ |
| IDB 被改 | 查询脚本 `qexit(0)` **不保存** ✓ |

## 9. 交付物

1. §3 的取证结论（`UISceneMap` 定谳或剔除 ✓；`ScreenEffectNode` 424 复核 ✓）
2. 证据表 + 计划/批（落盘 ✓）
3. 一次管线的**完整退出码 + 判据读数** ✓
4. 提交（或按 §7 回退并记录 ✓）
5. 台账更新（`data/status/_d1_ledger.md` ✓）
