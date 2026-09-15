# 决策页（草稿）：export 读 `data/annotations/` —— 有意取舍，本轮不迁移

> **状态**：**草稿**，由 t4 交付，待 captain → integrator（t12）落盘到 `docs/knowledge/`（建议 type=`decision`，文件名 `decision_export_reads_annotations_bridge_stage.md`），并在 `docs/knowledge/MEMORY.md` 的 `## Decisions` 段（**当前为空**）登记。
> **本文件不直接写入知识库**（t4 的 inScope 只有 `pipeline/ida/export_full.py`）。
> **生成时间**：2026-09-15 · **HEAD**：`9cb436305` · **取证产物版本**：`asm/pal3/ida_structs.json` sha256(16)=`3bf54cafe721d3e4`（mtime 15:44:30）+ `_logs/pal3_export_only_log.txt`（同次运行）
> **配套交付物**：`data/status/_cleanup_fix_export_redline.json`（逐读点清单 + 全部实测数字 + 命令）
> **相关裁决**：`docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md` 裁决 (a)（codegen 读注解 = C1）、裁决 (b)（同源证据的循环性）

---

## 0. 决策一句话

`pipeline/ida/export_full.py` **仍直接读 `data/annotations/`**（CLAUDE.md:69 红线：「export 不读 annotation：`export_full.py` 只能从 IDB 读取数据」）。
t4 判定为**有意取舍（exit b）**：删除其中唯一可判死的一处（原 `:148-154`），给余下 **8 处**加显式声明，并记下取舍与**迁移前置条件**。
**红线本身未被满足**——本决策页不是"用注释把 SHOULD 说成 OK"（裁决 (a) 明令禁止的收口方式），而是把存量违规登记为**有待撤回条件的已知例外**。

---

## 1. 事实基线（全部可复核，命令见交付物 JSON 的 `commands_run`）

| 项 | 值 |
|---|---|
| 读点数（改前 / 改后） | **9 → 8** |
| 删除的一处 | 原 `:148-154`（读 `functions.json`）——**死读**：AST 证明 `ann_funcs` 在 `:153` 赋值后**无任何读取**（唯一 Load 在 `:154`，只是 log 计数）。成因可追：`d827ebca6`(05-21) 引入「以注解 signature 为权威源」，`71a2e09db`(05-22) 删掉唯一使用点却留下 load |
| 该处注释 | `:148` 的 `authoritative source for signatures` **是失实的化石**（随块删除） |
| 余下 8 处 | 全部带 `[t4-DECLARED-EXCEPTION]` 标记（可 grep），行号 194/238/254/257/325/532/738/770 |
| 红线文本引入时间 | `6b6ac7fe5`（2026-06-09）——**晚于**"export 即桥"的实现（`18838d912`，06-05）；`ad527e5c2`(06-22)、`38f811d0f`(06-19) 是在红线写下**之后**继续扩展了桥模式 |
| 决策记载 | `docs/knowledge/MEMORY.md` 的 `## Decisions` 段**为空** → 这条架构事实从未被正式批准过 |
| 三层状态（本轮期间被窗口改过） | 本轮进行中 captain 侧跑了 apply(15:40:47)+export(15:44:30)、`.i64` 15:44:39：`asm/pal3/decomp` 全部刷新到 15:44:09，但 **`pal3/src` 无一文件在 15:20 之后被写**（最新 15:10:13）→ **codegen 未重跑**；`probe_census.json`/`baselines/latest.json` 15:11:21、`s4_baseline.json` 15:13:21 均早于该 export → 盘上是「IDB(新)→decomp(新)→pal3/src(旧)」＋旧基线。**L1/ok 的实测与可比性都须在窗口内连同 codegen/probe/match 一起重建。** |

---

## 2. 为何**必须**读（不读则信息不存在）

8 处读取中，有 6 处的信息**在当前 IDB 中没有等价可查询形式**（逐条实测）：

| 读点 | 读什么 | IDB 里有没有 | 证据 |
|---|---|---|---|
| `:238` | `skip_functions.json` → 1955 个 skip 地址 | **没有** | `apply_annotations.py:1676-1689` 对这些地址只做 `add_func` + `ida_name.set_name`，**不留任何 skip 标记**；而它**故意把它们造成函数**，所以 `idautils.Functions()` 一定会列出它们 —— 不读注解就没有任何依据把它们排除 |
| `:738` | `globals.json` 的 `type=="skip"`（196 条） | **没有** | `apply_annotations.py:1710` 显式把 `gtype=="skip"` 排除在 `SetType` 之外（`if name and gtype and gtype != "skip"`），IDB 只拿到名字 |
| `:770` | 非 thunk 的 skip 名单（1816 个） | **部分** | 名字被 apply 写进 IDB，但"哪些地址属于刻意 skip 且非 thunk"这一**集合语义**只在注解里；导出名与非 thunk 名单**集合完全相等** |
| `:532` | `structs/*.json` 的 `vtables`/`methods`/`known_members` | **部分** | 导出的这三个字段与注解**逐字段等值（761/761，0 不一致）** → 它们本来就取自注解文件，不是 IDB 读出量。IDB 侧只有 apply 加工后的 UDT 视图，且 `udt_classify.py:50-57` 会把名字含 `vtbl`/`__vftable` 的成员**过滤掉**；`vtables[].slots[].from`（继承来源）、方法 `name/signature` 表在 IDB 无持久化形态 |
| `:325` | `functions.json` 全地址表 | **没有** | 该表的用途正是"IDB 里还没有的函数地址"——IDB 无法自证不存在的函数 |
| `:254`/`:257` | `functions.json` + `structs/` → VC6 mangled 名 | **部分** | 签名/类名可从 IDB 推，但**等价性未验证**，且这段本身要写 3276 个名字进 IDB |

> 关键事实：`apply_annotations.py` **不产出任何可供 export 消费的元数据文件**——它的磁盘写入只有 `_logs/*.txt`、`gbengine_flat_ida.h`、sig-fail log（`grep "open(.*'w'\|json.dump"` 实测）。所以"让 export 读 apply 产物"这条路**当前不存在**，需要新建。
> 设计意图有原文自述：`18838d912`（2026-06-05）commit message ——
> `export_full.py: export globals from IDB, vtables/methods from annotations (export IS the bridge stage, reads annotations to produce final output)`，并在同一条 message 里宣布 `No cross-stage reads remain.`

---

## 3. 不读会失去什么（当前规模，全部实测）

| 读点 | 失去的东西 | 实测数字 |
|---|---|---|
| `:238` | 语料组成（1955 个地址不再被排除） | 1955 条全落在 `.text`；与 3594 个实际导出地址**交集=0**（排除完全生效） |
| `:194` | 虚性 + 类归属 | `_virtual_addrs=475` / `_addr_to_class=369`（离线复现与运行日志逐字一致）→ 导出语料中 **442/3594** 个 `signature` 以 `virtual ` 开头；**3199/3594** 个 `name` 含 `::`，其中 **34** 个是 `ClassName::sub_XXXX` 形态（必为注入，下界） |
| `:254`/`:257` | 函数名唯一化 | `[*] Mangler: set 3276 mangled function names` |
| `:325` | 未定义函数补录 | 当前 `recovered=0`（2 条不可恢复）→ 本轮零贡献，**保留理由是换库/重建 IDB 的稳健性** |
| `:532` | `ida_structs.json` 的 `vtables`/`methods`/`_variants` | 79 个 struct 带 vtables、215 个带 methods、686 个带非空 `_variants`（**8979 条**条目）；下游消费者 `emit_headers.py` 13 处 + `data.py:141` + `stage3_cleanup.py:100` |
| `:738` | globals 的 skip 语义 | 196 条注解 skip → **188** 条落进 `_globals`（导出 skip 总数 808，另 620 来自 `.rdata` 过滤） |
| `:770` | codegen 的 skip 名集 | 1816 个名字，消费者 `pipeline/gen/data.py:188` |

**结论**：这些不是"顺手的额外信息"，而是直接决定导出语料（3594 个 decomp JSON）与 `ida_structs.json` 内容于是决定 codegen 输出的承重输入。

---

## 4. 读的后果（诚实列出好处之外的一面）

1. **`ida_structs.json` 的三个字段不再是 IDB 的证据。** 实测它们与注解文件 0 不一致（761/761）——无论 IDB 状态如何都长这样。任何用 `ida_structs.json` 校验"apply 是否真把注解落进 IDB"的检查，在这三个字段上**必然被误导**；而这正是 t3 要防的失效模式（`TAUDT_FIXED` → `get_size()==-1` → 静默留下空壳）。
2. **存在两源混合的机制风险。** 若某 struct 的注解 UDT 未落地、IDB 仍留着 PDB 版类型，`:631-634` 会把注解的 `vtables`/`methods`/`_variants` 嫁接到 PDB 形状的 `data_members` 上（前者来自文件、后者来自 IDB）。
   **是否实际发生：未验证**（本轮无 IDB 窗口）。反向对照：**818/818** 个可比 struct 的 `export.size == 注解 binary_size`，未见尺寸级落地失败。
3. **旁路效应。** 注解改动只要跑 `export`（**不需要 `apply`**）就能改变 codegen 的输入，绕过 apply 的校验链（`member_end`/`binary_size`/UDT 落地复核）。
4. **证据天花板。** 与裁决 (b) 同理：本类"读注解→写产物"使 `ida_structs.json` 不能作为任何独立证据源（同源比对只会自证）。
5. **附带发现（同类失实自述）**：文件头自称 `Pure export - no modifications to IDB`，但 `:206-264` 的 mangler pre-pass 会执行 **3276 次 `ida_name.set_name`（写 IDB）**。已在此登记，未改（与红线无关，不做无关重构）。

---

## 5. 为何**此时不迁移**（四条，均为实测/硬约束）

1. **纯 IDB 取数不可能等价** —— 第 2 节已证 6 处信息在 IDB 中不存在或不完整。改了就**改变导出产物**，那是行为变更，不是等价重构；因此 (a) 出口的"等价性证明"在这 8 处上**不可能成立**。
2. **本轮的等价性无法测量** —— 判据要求 `match`（L1）与 `probe`（ok）的实测值，而 (a) 还额外要求"导出产物 diff"（3594 个 decomp JSON + `ida_structs.json`）。`export`/`probe`/`match` 都写共享产物（`compare_pal3.py` 写 `data/status/s4_baseline.json`、export 写 `asm/pal3/`），本轮窗口被 t3 的 apply/export 占用（实测 15:40:47 apply 日志、15:44:30 export 日志、15:44:39 `.i64` mtime）——按窗口纪律不得并发。
3. **迁移必然连带其它模块（越界）** —— 要落地 (a)，必须先让 `apply_annotations.py`（或新增独立 IDB dumper 脚本）把 skip 集合 / globals skip / skip 名单 / structs 元数据以"**从 IDB 状态生成**"的形式落盘。t4 的 inScope 只有 `export_full.py`，按任务边界须先回报 captain。
4. **风险面不划算** —— export 是该管线的**唯一桥**（`:18838d912` 自述），其输出驱动 `emit_headers.py` 13 个消费点 + `data.py:188`。在没有窗口验证的情况下改写桥的取数来源，正是裁决 (a) 警告的旁路类改动。

---

## 6. 迁移前置条件（将来要做 (a) 时的 Definition of Ready）

1. `apply`（或独立 IDB dumper）产出 **IDB 派生的元数据产物**，至少含：
   - `skip` 地址集合（apply 需在 IDB 写入可查询标记，如专用 comment/命名前缀/单独段落）；
   - `globals` 的 `skip` 语义（同上，且需解决 name 不一致时的归属规则——现有 8/196 走的是"name 匹配才置 skip"策略）；
   - 非 thunk 的 skip 名单；
   - `vtables`/`methods`/`known_members` 的**等价表达**（含 `slots[].from` 继承来源、方法 `name/signature`）；
   - 建议同时落地 `_virtual_addrs`/`_addr_to_class` 的 IDB 推导（读 `vtbl_*` UDT 持有者 + vftable 数据的 slot 地址）。
2. **等价性判据**：改后 export 必须产出**逐字节相同**的 3594 个 `decomp/*.json` + `ida_structs.json`（除日志文本），并给出 diff 证据。
3. 若等价无法达成，必须**逐项列出行为差异**（哪个字段、影响哪些 struct 数、影响哪些 codegen 消费点）并由用户裁决是否接受。
4. 落地后：`L1 ≥ 5`、`ok ≥ 53/198`、分母 198 不变。

---

## 7. 保留条件与撤回条件（按 t5 规则 C2 的契约）

**保留条件（必须维持，否则本条应从"有意保留"降级为"缺陷"）**
1. 每个读点都带 `[t4-DECLARED-EXCEPTION]` 标记，`grep` 可数（当前 = 8）。
2. 文件头声明块与 `data/status/_cleanup_fix_export_redline.json` 中的实测数字保持可复核（若改注解/改 apply 使数字漂移，须重取并更新）。
3. 不得在**未更新本决策页**的情况下新增第 9 个读点。

**撤回条件（满足任一条即应执行迁移）**
1. 上面第 6 节的前置产物落地且等价性 diff 通过。
2. 用户/团队决定**修改 CLAUDE.md 的红线**，把它从"export 只能从 IDB 读取数据"改成明文承认"export 是 annotation→IDB→codegen 的桥，允许读注解"——此时本条从"违规例外"转为"已批准架构"，**决策页应改写为架构说明**，且 `docs/knowledge/MEMORY.md` 的 `## Decisions` 段必须有记载。
3. 出现一次"因该旁路导致导出产物与 IDB 状态不一致且下游被误导"的实例（第 4 节第 1/2 条从机制风险变成观察到的事实）。

---

## 8. 需要用户/captain 决策的开放问题

1. **CLAUDE.md:69 是否修改？** 三条路：(i) 维持红线，按第 6 节做迁移（成本高，需新产物 + 全量 diff）；(ii) 修改红线，明文承认桥模式（成本低，但需在 `docs/knowledge` 留决策）；(iii) 维持红线 + 保留本例外并登记（t4 当前交付的形态，红线继续处于"已知未满足"状态）。
   > 裁决 (a) 对同类问题给出的两条合法收口路径正是 (i)/(ii)；本页把选择权交回用户，**不自行把 SHOULD 说成 OK**。
2. 若选 (ii)/(iii)，是否需要**先澄清一个前置矛盾**：`codegen` 侧同类读取已被裁决 (a) 判 C1 并要求迁移，而 export 侧（本条）若被批准为合法例外，两者的判定必须在知识库里**分开表述**，避免"上游允许、下游禁止"的误读。
3. `docs/knowledge/MEMORY.md` 的 `## Decisions` 段当前为空——本条落盘时应同时补上索引行（t12）。

---

## 附：复核命令（只读，任何窗口都可跑）

```bash
cd /home/peng/workspace/PAL3Decomp
grep -n "\"annotations\"" pipeline/ida/export_full.py          # 应打印 8 行（新行号 194/238/254/257/325/532/738/770）
grep -c "t4-DECLARED-EXCEPTION" pipeline/ida/export_full.py     # 应为 9 行 = 声明块 2 行 + 7 处标记（其中 1 处标记同时覆盖相邻的 2 个读点）
python3 -c "import ast;ast.parse(open('pipeline/ida/export_full.py',encoding='utf-8').read());print('OK')"
python3 -c "import json;d=json.load(open('data/status/_cleanup_fix_export_redline.json'));print(d['exit_chosen'],d['read_sites_before_count'],d['read_sites_after_count'])"
cat pipeline/ida/_logs/pal3_export_only_log.txt | grep -E "Loaded|Mangler|Recovered|Exported|skipped"
```