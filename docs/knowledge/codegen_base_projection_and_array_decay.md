---
name: codegen-base-projection-and-array-decay
description: 两个独立 codegen 坑的可复用规律：注解有 bases 但缺 base_size 会让成员整体错位；stage5 把数组成员一律当值会让 unsigned char[8] 赋值触发 C2440。含根因链路、六项布局判据、回归测试与复用清单。
type: gotcha
created: 2026-11-26
sources: [ac9c67673, tsk_01M8BYKHXM15J0SRFP2F57, tsk_01M8BX8WS2XASCCC5Z9VXV, data/status/base_projection_fix_20261126.md]
---

# 基类投影 base_size 与数组退化指针分类：两个 codegen 坑

**一句话**：`RoleStatePanel.cpp:777` 的 C2440 和成员整体 `+0x2A8` 是两个独立根因，不是同一个 bug。前者是 `stage5_fixup._path_is_pointer` 把数组成员判成值；后者是注解有 `bases` 却缺 `base_size`，apply 跳过基类子对象、export 的 `bases=[]`、生成头按 `base_size=0` 排成员。两个都修完，编译和偏移才同时回正。

> **状态（写作时 2026-11-26）**：#6、#8 已验收，但截至 HEAD `9f4436c2b`，两处注解改动仍是工作树 `M`，两个测试和 `stage5_fixup.py` 改动仍是 `M`/`??`，没有 git commit。本文按「已验收、未提交」引用，不写成「已提交/已生效」。R3 的 `ac9c67673` 引入 `m_bRtVisible` 是暴露触发点，不是根因。

## 1. 现象：五个观察，两个根因

| 症状 | 实测 | 对应根因 | 证据 |
|---|---|---|---|
| `RoleStatePanel.cpp:777` 编译失败 | `C2440: '=' : cannot convert from 'char [8]' to 'unsigned long *'` | **B 数组退化分类** | `data/status/probe_census.json` 2026-11-26T19:14:46；#1 报告 §1 |
| `offsetof(m_bRtVisible)` 偏大 | 0x25E20 vs 原始 0x25B78（Δ +0x2A8） | **A 基类投影** | `data/status/base_projection_fix_20261126.md` §1；逆证头 `/tmp/prefix_repro/ovr/Misc/*.h` |
| `offsetof(m_unk_0x174)` 偏大 | 0x1B8 vs 原始 0x174（Δ +0x44） | **A** | 同上 |
| `sizeof(UIFrameContainer)` 偏大 | 220（0xDC） vs 注解 152（0x98） | **A** | 同上；`sizeof(RoleStatePanel)` 177956 vs 176256 |
| L1 丢掉 `0x4A2150` 的 30B 删除析构 | L1 189→188；该单元 17 条 partial + 1 条 L1 整组退出比对 | **B 的下游** | #1 报告；`pipeline/_logs/loop_match.log` 19:29:02 |

关键区分：

- **A 不导致 C2440，B 不导致偏移漂移**。只修 A，777 行仍编译失败；只修 B，能编译，但两笔 dword 会落在 0x25E20/0x25E24，不是原始的 0x25B78/0x25B7C。
- L1 丢 30B 不是字节比对退化，而是 C2440 让整个编译单元 `status=fail`；match 只比对 S2 通过单元，于是该单元的 17 条 partial 和 1 条 L1 一起退出可比域。

## 2. 根因 A：bases 有、base_size 缺失，基类子对象没进 IDB

链路（每一跳都有代码或产物）：

1. `data/annotations/structs/RoleStatePanel.json` / `UIFrameContainer.json` 写了 `bases`，但原来没有 `base_size`。
2. `pipeline/ida/apply_annotations.py:988` 读 `base_size = struct_info.get("base_size", 0)`；`:1047` 只有 `if _concrete_bases and base_size > 0:` 才把基类子对象 `push` 进 UDT。**单继承不会自动推导**，缺字段就直接跳过。
3. 导出 `asm/pal3/ida_structs.json` 里这两类变成 `bases=[]`（`UIListBox` 自己是正常的 `bases=[UIWnd@0]`）。
4. `pipeline/gen/stages/emit_headers.py:2754` 先读导出里的 `base_size`（导出数据里恒不存在），`:2765` 再从 `bases[]` 反推 `base_size = max(b.offset + size(b.name))`；`bases=[]` ⇒ `base_size=0`。
5. 但类声明仍写 `: public UIListBox`，基类名来自注解（`:2415-2433`）⇒ 生成头从 `+4` 起排（`_gap_004[84]`），编译器按基类 72B 从 `+0x48` 起 ⇒ 实测偏移比注解多 `0x44`。
6. `UIFrameContainer` 自身少 `72-4=68`，又被 `RoleStatePanel` 按值内嵌 9 个，叠 `9×68=0x264` ⇒ 总漂移 `0x68+0x264=0x2A8`。

修法（annotation 层，一行）：

```diff
 data/annotations/structs/RoleStatePanel.json
     "bases": [ ... ],
+    "base_size": 72,
 data/annotations/structs/UIFrameContainer.json
     "bases": [ ... ],
+    "base_size": 72,
```

- `72` 是 `UIListBox` / `UIFrameWnd` 的 `binary_size`，不是 `UIWnd` 的 68；写错会让偏移继续漂 4B。
- 不选「codegen 经 `annotation_view` 读注解 bases」的 fallback：apply→export 是唯一真相链，IDB 缺基类子对象本身就是标注缺陷；codegen 兜底只会把缺陷藏起来，还多一个注解读点。

修后六项判据（编译器实测，全部回到原始值）：

| 判据 | 值 |
|---|---|
| `offsetof(RoleStatePanel, m_bRtVisible)` | 0x25B78 |
| `offsetof(RoleStatePanel, m_unk_0x174)` | 0x174 |
| `offsetof(RoleStatePanel, m_nRtIndex)` | 0x25B80 |
| `offsetof(UIFrameContainer, m_bFlag96)` | 0x60 |
| `sizeof(UIFrameContainer)` | 152 |
| `sizeof(RoleStatePanel)` | 176256 |

## 3. 根因 B：数组成员被一律当值，Family2 不补 cast

链路：

1. 777 行原形是 `m_bRtVisible = this->m_bRtVisible;`，成员声明 `unsigned char[8]`，左侧局部是 `unsigned long *`。
2. `pipeline/gen/stages/stage5_fixup.py:871` 调 `_path_is_pointer(e, vt, ctx, array_decays=('[' not in e))`；`:779` 定义里 `:811` 只判 `if '*' in mt: return True`，`unsigned char[8]` 不含 `*` ⇒ False（`:813` 的数组退化分支只在 `array_decays=True` 且是最后一段时生效）。
3. `_expr_is_pointer` 返回 False ⇒ `_fix_line_plain_var_assign`（`:995`）直接原样返回，不补 cast ⇒ C2440。

修法（核心逻辑约 4 行，实际 diff +10/−3，复用已有 Family2 cast）：

- `_path_is_pointer(path, vt, ctx, array_decays=False)` 增加形参；
- 循环里用 `idx == last` 锁定**最后一段成员**，仅当 `array_decays=True` 且成员类型以 `[...]` 结尾时返回 True（`:813`）；
- 调用点传 `array_decays=('[' not in e)`（`:871`）——源码无下标才退化。

行为边界（`tests/test_stage5_array_decay.py` 六条）：

| 表达式 | 结果 | 原因 |
|---|---|---|
| `this->m_bRtVisible` | True | 数组在值语境退化为首元素指针 |
| `this->m_bRtVisible[2]` | False | 带下标是元素值，不能当指针 |
| `this->m_pPtr` | True | 指针成员原行为不变 |
| `this->m_iFlag` | False | 标量原行为不变 |
| Family2 无下标 RHS | 产出 `(unsigned long *)this->m_bRtVisible` | 过 C2440，保住 8B 写 |
| Family2 带下标 RHS | 原样不动 | 不能把元素值转成指针 |

为什么不用别的方案：

- 局部声明成 `char *`：能过编译，但写入退化成 1 字节（`mov BYTE [esi+…],bl`），8 字节清零语义丢失。
- 声明成 `void *`：不可解引用，触发 C2100/C2036/C2120。
- 成员改 `unsigned long[2]`：元素宽度 4B→8B，`&member[4]` 从 `+0x4` 变 `+0x10`，索引读步长 1B→4B，布局与访问形态双崩。
- 直接在 `pal3/src/Misc/RoleStatePanel.cpp` 手改 cast：产物会被下一次 codegen 覆盖，落点必须在 generator。

影响面（快照：2026-11-26 22:59 的当前树，含 SaleUI 未提交改动）：把 `git show HEAD:pipeline/gen/stages/stage5_fixup.py` 存成 HEAD 版，对当前 `pal3/src` 每个 `.cpp` 的每一行分别跑 HEAD 版与现版的 `_fix_line_plain_var_assign`，取「HEAD 原样返回、现版补了 cast」的行，得到 **66 行 / 25 个单元 / 45 个不同成员**（`buf` 出现 9 次最多）；其中 SaleUI 16 行，该类注解在 R5 后仍有未提交改动。66 行的 RHS 全是 `this-><member>` 且不含下标；真正因此编译失败的只有 `RoleStatePanel` 这 1 处。这个数是快照，不是恒定值；复跑要在无并发 loop、`pal3/src` 不被重建的窗口做。其余命中是否字节中性要逐处看，不能按「数组名」一概而论。

## 4. 验证与读数（必须带轮次和时点）

| 轮次 | 读数 | 说明 |
|---|---|---|
| 基线 2026-11-26T19:14:46 | S2 157/229，总错误 633，L1 实况 188（棘轮基线 189） | 改前；RoleStatePanel.cpp 唯一错误 C2440@777 |
| #8 布局修复 21:01:14 | S2 160/229，总错误 608；match L1 189→194 | **全链累积读数**，工作树还有他人未提交改动，不能全归因给 base_size；L1 自动棘轮回写后按卡边界 checkout 还原到 189，未 `--rebaseline` |
| #6 cast 修复 22:04:46 | loop S2 158/229；RoleStatePanel.cpp = ok/0 错误；match L1 189；`0x4A2150` 30B 删除析构回 L1 | 独占窗口 loop；match 读数见该轮日志 |

读数注意：

- S2 160 和 158 是不同轮次、共享工作树的读数，**不能相加或当成同一改动的增量**。#8 报告 §7 已写明 157→160 不能全部归因给 base_size；base_size 的直接因果证据是测试 6×C2118→3 passed、`audit_type_layout` 冲突 68/67→仅 `tail_drift`、生成头 `_gap_004[84]`→`_gap_048[16]` 且 `ida_structs.bases` 由空变非空。
- L1 194 只存在于 #8 那轮日志与报告；#8 已 checkout 还原基线到 189。之后 #6 的 match 也是 189，并把 `0x4A2150` 30B 恢复到 L1；没有重锚。
- 两处改动截至写作时都未 git commit；不要把「测试通过」写成「已提交/已生效」。

测试与命令：

```bash
# 根因 A：注解两层 + 编译器静态断言（需 MSVC6/wine）
python3 -m pytest tests/test_base_size_projection.py -q
# 修复前：6 条 C2118（逆证头 /tmp/prefix_repro/ovr/Misc/*.h）
# 修复后：3 passed

# 根因 B：数组退化分类 + Family2 产物
python3 -m pytest tests/test_stage5_array_decay.py tests/test_stage5_propagate_types.py -q
# 6 passed, 3 skipped
```

`0x4A2150` 30B 删除析构回 L1 的物证：`data/status/s4_l1_identity_cur.json:598-599` 出现 `["RoleStatePanel::\`scalar deleting destructor'(uint)", 4858192, 30]`（#6 轮存档于 `/tmp/s6_evidence/l1_identity.json`）；OnMessage 两笔 dword 的 objdump：`/tmp/s6_evidence/objdump_25b78.txt`，`89 9e 78 5b 02 00` / `89 9e 7c 5b 02 00`，地址 0x25B78/0x25B7C。`/tmp` 可能被清理，长期引用以卡内证据和 `data/status` 归档为准。

## 5. 何时使用：复用清单

1. **新增/修改 `bases` 必须同时写 `base_size`**，值取基类自身的 `binary_size`（不是 `UIWnd` 的 68，也不是首个成员偏移）。`apply_annotations.py:1047` 只认 `base_size>0`，单继承不会自动推导。
2. **改布局后先比 `offsetof`/`sizeof`，再看报错**。`audit_type_layout` 的 68/67 全冲突、`_gap_004[84]` 都是 A 的信号；C2440 文本不能证明布局对。
3. **数组退化只在值语境、最后一段成员、源码无下标时成立**。任何 `member[i]` 都是元素值，不能套 `array_decays`。
4. **不改生成物 `pal3/src`**。cast 或布局都回 annotation/codegen 层修，否则下一次 codegen 覆盖。
5. **两个根因分开验证、合起来验收**：A 修完仍会 C2440；B 修完仍会清错地址。顺序按「布局 → cast → 全链」，验收同时看编译、六项偏移、两笔 dword 地址、dtor L1。
6. **读数只认独占窗口的完整 loop**，并记录 `generated_at`；L1 棘轮自动回写后按卡边界 checkout 还原，不用 `--rebaseline` 把一次性读数固化。
7. **预期 cast churn**：按 22:59 当前树对拍是 66 行 / 25 单元 / 45 个成员（含 SaleUI 未提交 16 行），review 时逐处确认 cast 是否改变指令宽度或语义，不要按源码行数判断退化；复跑须避开并发 loop。
8. **三态写清**：已验收 ≠ 已提交 ≠ 已生效。本文两处改动在工作树，HEAD 不含；引用时带 `M`/`??` 和 HEAD。

## 6. 引用索引

- 证物报告：`data/status/base_projection_fix_20261126.md`（#8 根因/六项判据/测试/读数/边界）、`data/status/match_red_attribution_20261126.md`（#1 L1 归因）、`data/status/lvar_feasibility_20261126.md`（#2 说明为什么只改声明行不够）。
- 卡：#8 `tsk_01M8BYKHXM15J0SRFP2F57`、#6 `tsk_01M8BX8WS2XASCCC5Z9VXV`、#1 `tsk_01M8BW9PT0DT4XBQ7TMX01`、#2 `tsk_01M8BWFAS4FT282VX3NPP2`。
- 代码：`pipeline/ida/apply_annotations.py:988,1047`；`pipeline/gen/stages/emit_headers.py:2415-2433,2754-2765,2817-2825`；`pipeline/gen/stages/stage5_fixup.py:779,813,871,995`。
- 注解：`data/annotations/structs/RoleStatePanel.json:712`、`data/annotations/structs/UIFrameContainer.json:162`（工作树 `base_size: 72`）。
- 测试：`tests/test_base_size_projection.py`、`tests/test_stage5_array_decay.py`。
- 日志/物证（临时目录，可能已清）：`/tmp/s6_loop.log`、`/tmp/s6_match3.log`、`/tmp/s6_evidence/`、`/tmp/prefix_repro/pre.log`。
- 触发提交：`ac9c67673`（R3 引入 `m_bRtVisible`，暴露 B）；#6/#8 本身截至写作时无 commit。
