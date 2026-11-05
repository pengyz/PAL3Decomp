# 独立对抗性复核：《L1 诊断工具层（oot 借鉴三件）》设计 spec

- 复核对象：`docs/specs/2026-11-05-l1-diagnosis-tools-design.md`（75 行，下称 spec）
- 复核方式：只读实码 + 实测数据（compare_pal3 / gbengine_compare / probe_compile / cli / 既有 diff 工具 / 三份 status 数据文件）
- 铁律：不准确=不判定；本报告中所有未实测项集中列于 §5「未复验」
- 复核时点：2026-11-05（读数为当时盘面）

---

## 0. 总裁：**需改**（方向可行，3 处硬伤落地前必须修）

三件工具本身**可行**，且数据面比 spec 预期更"现成"——但有 3 处硬伤 + 2 处事实性偏差：

| # | 结论 | 一句话 |
|---|------|--------|
| 硬伤 A | **对账断言不可按字面执行** | 「L1 列总和 = s4 棘轮 matched」中 `matched` 是另一个键（924 ≠ 161）；且 L1 取 baseline、partial 取 detail **两文件已实证不同源**（detail.l1=110 vs baseline=161） |
| 硬伤 B | **obj 生命周期是真盲区** | 编译产物在 `/tmp/pal3_probe`，**每次 probe 结束即 rmtree**；spec 全文未提 obj 缺失回退与编译 flags 复用 |
| 硬伤 C | **序与 handoff 不一致且未声明** | handoff `序：2→3→1`（progress→asm→first_diff），spec 实为 2→1→3 |
| 偏差 D | §0「无工具面/靠人肉对字节」与实况不符 | `tools/fdiff.py`、`tools/byte_diff_explain.py` 已提供首差+双侧反汇编+对齐首分歧（实测跑通） |
| 偏差 E | 「自建 ~200 行 asm_diff」重复造轮 | 仓内已有 `difflib.SequenceMatcher` 指令对齐 + 分支目标归一 + capstone 5.0.7 实测可用 |

**可保留**：byte_source 单源理念、TDD 红绿序骨架、fail-loud 风险处置（spec:73-75）、预存 7 失败零新增判据（实证 7 failed ✓）。

---

## 1. 逐条证据核对（必攻 6 条）

### 1.1 数据源可行性：装载面到底什么形

**结论：spec 的「复用装载逻辑不重造」方向成立，抽取成本未被显著低估；但 spec 漏查了 2 件事（flags、现成通用 PE 解析）。**

实码证据：

- **编译字节装载 = 3 段可独立复用的纯函数，不耦合 match 流程**：
  - COFF 解析：`tools/gbengine_compare.py:87-237`（`parse_coff_obj`，模块级纯函数，仅读文件）；
  - obj 命名约定：`pipeline/compare_pal3.py:466`（`s4_<md5(unit)[:8]>.obj`，稳定哈希）；
  - 截断比较：`pipeline/compare_pal3.py:509`（`compiled = info['bytes'][:size]`）+ `tools/gbengine_compare.py:292-403`（`compare_bytes`）。
  - **先例已存在**：`tools/fdiff.py:26-29` 直接 `import probe_compile as pc` / `from compare_pal3 import exe_text_image` / `import gbengine_compare as gc` 并跑通（本复核实测 `python3 tools/fdiff.py CCBAI GetTargetRole` 正常输出双侧反汇编）⇒ "内部耦合 match 流程、抽取成本被低估"的担忧**不成立**（低耦合）。
- **compare_pal3 并没有"装载已有 obj"的函数**：`compare_pal3.py:467-475` 是「当场 wine 重编 → `parse_coff_obj`」，装载逻辑本身可复用，**但"按需取某单元 obj"的入口（存在则用、缺失则单单元重编）仓内不存在**——`tools/fdiff.py:64-67` 的处置是直接 fail-loud 让人重跑整场 match。spec:33「复用装载逻辑」只覆盖了解析半边。
- **⚠️ flags 陷阱（spec 未写，会导致首差错位）**：`pipeline/cli.py:737` 的 match 实际用
  `"/nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MT /Gd"`（hypothesis 组，`data/status/s4_diff_detail.json.flags` 实测同值）；
  而 `pipeline/compare_pal3.py:429-433` 的 `PROBE_FLAGS` 只有 `/nologo /TP /c /W3`。
  first_diff 若缺省用 `PROBE_FLAGS` 重编，字节与棘轮基线**必然不同** ⇒ 首差是假的。spec §1.2/§2 未提 flags 复用。
- **原字节 VA→file offset：现成的有，spec 没点名（漏洞但不致命）**：
  - 通用 PE 解析（全节表 + RVA→offset + 绝对地址读）：`tools/compare_exe.py:102-131`（`PEParser.rva_to_file_offset` / `read_bytes_at_address`）——spec:49「复用现有 PE 解析**若有**」的答案是「**有**」；
  - `.text` 专用三份并存：`pipeline/compare_pal3.py:76-101`（`exe_text_image`）、`tools/byte_diff_explain.py:46-62`（`load_text`，独立第三份）、`tools/gbengine_compare.py:36-84`（`get_dll_text_section`，且 68-74 行返回体里混入了未定义名 `'reloc_target'`，gbengine 专用路径**实为坏的**，不可复用）；
  - VA→.text 内偏移公式：`pipeline/compare_pal3.py:495`、`tools/fdiff.py:113`（`va - image_base - text_rva`）。
  ⇒ **spec §2 自称「单源」，但仓内已有 3 份 .text 解析**；byte_source 若再写第 4 份，违反其自身 TOS 单源纪律（spec:52）。正确做法是**收敛现存 3 份**而非新增。

### 1.2 match_progress 对账断言：partial 行语义下成立吗

**结论：字面判据不成立/有歧义；跨文件混源已被实测证伪。**

盘面实测（2026-11-05 读）：

| 读数 | 值 | 出处 |
|---|---|---|
| `s4_baseline.stats.matched` | **924** | `data/status/s4_baseline.json` |
| `s4_baseline.stats.match_L1` | **161** | 同上；`pipeline/cli.py status` 打印「s4_baseline.json L1 棘轮=161」 |
| `s4_baseline.stats.partial` | **690** | 同上 |
| `s4_baseline` rows | 851（=161+690）· 覆盖 **131** 单元 | 同上 |
| `stats.unresolved_synth` | **73**（计入 matched、无 status 行） | `pipeline/compare_pal3.py:479`（先 `+= len(matched)`）与 `:491-493`（无 `va` 跳过比对） |
| `s4_diff_detail.l1 / partial` | **110 / 542** | `data/status/s4_diff_detail.json`（写入点 `pipeline/compare_pal3.py:855`） |
| `s4_diff_detail` 行 / 单元 | **541 行 / 116 单元** | 同上（与任务背景 541/116 一致 ✓） |
| probe_census | S2 **128 ok / 215 total**，generated_at `2026-11-03T20:18:55` | `data/status/probe_census.json` |

逐点裁定：

1. **「L1 列总和 = matched」按字面恒假**：同文件内 `sum(status==match_L1) = 161 = stats.match_L1` ✓ 成立；但 `stats.matched = 924`（含 73 个 unresolved_synth，它们**没有 status 行**，`compare_pal3.py:491-493`）。
   ⇒ 断言必须写成**精确键名** `sum(L1 列) == s4_baseline.stats.match_L1`；写 "matched" 就是把 161 对 924 的恒假断言。
2. **partial 不能取自 s4_diff_detail 与 L1（取自 baseline）混拼**：两文件已实测不同源——
   - 同秒级 mtime（`2026-11-04 10:04:56.76` / `...75`）但 `detail.l1=110 ≠ baseline.stats.match_L1=161`、`detail.partial=542 ≠ baseline.partial=690`；
   - 集合差：baseline-partial 有 **193** 个不在 detail；detail 有 **44** 个不在 baseline-partial（其中 43 个在 baseline 中**根本无此行**、1 个在 baseline 中是 **match_L1**（状态相反））；
   - 单元集：baseline partial 覆盖 123 单元，detail 覆盖 116（10 个只在 baseline、3 个只在 detail）。
   - `pipeline/cli.py status` 当前只认 baseline（161）⇒ 权威读数与 detail 互相矛盾。
   - **最可能成因（未复验）**：L1 棘轮在退化时**回写旧 baseline**（`pipeline/cli.py:729` 读 prev_text → `:793-794` `s4.write_text(prev_text)`），而 detail 由 compare_pal3 无条件写新 run（`pipeline/compare_pal3.py:853-858`，无回写联动）⇒ 一次退化 match 就能造出"旧 baseline + 新 detail"。CLAUDE.md 已警告"不能事后查基线文件判断退化"，spec 恰恰在做**跨文件事后聚合**。
3. **同函数会不会既 partial 又别的？**
   - **同一次 run 内不会**：每符号一行、status 单值（`compare_pal3.py:655-657`），`match_L1+partial = rows = 851` 实测自洽；tail-jump 降级只会 L1→partial（`:521-538`），且降级样本 `stats.tail_jump_downgrades=1`——**但降级后的行不在 detail 里**（detail 追加判据是 `res['perfect']`，`:658`，早于降级改写 status）⇒ 即使同 run，detail 也是 baseline partial 的**真子集**（差 1 就是这 1 个降级）。
   - **跨文件会**：上表 44 个里有 1 个在 baseline 是 `match_L1`、在 detail 是 partial ⇒ **状态相反已实证**。
   - 另有 `status='out_of_range'` 第三种行（`compare_pal3.py:506-508`，当前 oob=0 才没出现），聚合时必须归入"不可比"而不是丢弃。
4. **行数=215**：census `s2.total=215`（含 fail）✓ 可达成（表含 S2 fail 行、置底，spec:26 合理）；但 baseline rows 只覆盖 131 单元，与 census ok(128) 集合差 **9 个 rows 单元非 ok / 6 个 ok 单元无 rows**（陈旧/交集问题）⇒ join 会产出"无基线"行，spec 未定义其状态列语义。

### 1.3 asm-differ x86 判定：「未验=先自建」与 200 行估计

**结论：200 行估计有旁证（不离谱），但"自建"前提不成立——要自建的东西仓内已有。**

- **既有件 1（批量·含对齐）** `tools/byte_diff_explain.py`（**全文 201 行**）：
  - capstone 双侧反汇编，reloc 操作数归一 `{R}`（`:65-75`）、call/jmp 目标归一 `{T}`（`key()` `:78-79`）；
  - **双侧 base=0 反汇编**避免分支绝对地址渲染造成假分歧（`:143-145` 注释，含实测 FindInOpen 案例）；
  - **`difflib.SequenceMatcher` 指令序列对齐**（`:148`）+ 首个分歧点抽取（`:152-163`）+ 原因分类 `classify`（`:82-112`，含 cond-jump 符号位、this 寄存器、立即数等族）+ adjustor-thunk 单列（`:169-175`）。
  - 输出 `data/status/s4_diff_explain.json`（mtime **2026-10-08**，已陈旧 28 天——它是按当时 detail 跑的）。
- **既有件 2（单函数·无对齐）** `tools/fdiff.py`（165 行）：双侧 hex + capstone 反汇编并排、reloc 标 `[r]`、差异行标 `<>`（`:136-149`），**本复核实测跑通**。它是**偏移对齐**（按 offset join），在插入/删除后会错位（实测输出可见 ORIG/OURS 交错）——这正是 spec `align_disasm` 想解决的点。
- **依赖面**：`capstone 5.0.7` 实测可 import；`objdump`（GNU Binutils 2.38）在位但仓内 objdump 用法集中在审计类（`tools/audit_member_use_pattern.py:32` 等），**没有**"objdump 局部反汇编→解析→对齐"的现成封装。
- **裁定**：
  - "自建 ~200 行"的量级**有依据**（byte_diff_explain 全文 201 行即覆盖对齐+分类+直方图）；
  - 但 spec:39-40「自建对本项目是 ~200 行级（双侧 objdump/可选 capstone→按序对齐）」把 **objdump 列为首选**与仓内既有 capstone 面分叉，且 spec:73 自己已把"objdump 输出解析脆"列为风险 ⇒ **更省的既有件=有**（byte_diff_explain 的 disasm/key/align/classify 直接可抽），应当复用而非并行新写；
  - "分支密集错位"处置：既有实践是①call/jmp 目标归一 `{T}` ②双侧 base=0 ③首分歧以**字节 offset 为准**（spec:75 也这么写 ✓）——三点都已在 byte_diff_explain 落地，spec 未引用。

### 1.4 first_diff 数据链：obj 在哪 / 生命周期

**结论：盲区成立——spec 没写 obj 生命周期，而 obj 是易失的。**

- **obj 位置**：`/tmp/pal3_probe/s4_<md5(unit)[:8]>.obj`
  - 目录定义 `pipeline/probe_compile.py:40-41`（`OBJ_DIR = /tmp/pal3_probe`）；
  - compare 写入 `pipeline/compare_pal3.py:466`；
  - **销毁点**：`pipeline/probe_compile.py:300` `shutil.rmtree(OBJ_DIR)` —— **每次 probe 结束无条件清空**。
- **detail 里记录的 obj 路径会失效**：`pipeline/compare_pal3.py:661`（`'obj': obj` 写进每条 partial 行）；`tools/byte_diff_explain.py:124-126` 对缺失的处置只是计数 `'(obj missing)'`；`tools/fdiff.py:64-67` fail-loud 并提示"先跑 cli.py match"。
- **盘面实测**：`/tmp/pal3_probe` 现有 **128 个 `s4_*.obj`，mtime 全部 2026-11-03 20:29**，而 `s4_diff_detail`/`s4_baseline` mtime 为 2026-11-04 10:04、census generated_at 2026-11-03 20:18 ⇒ **obj 与 detail/ baseline 三者并非同一时刻产物（未复验成因）**；detail 541 行的 obj 路径当前**全部存在**（实测 missing=0），但下一次 `probe` 即全灭。
- **spec 缺口**：§1.2「S2-ok 单元 obj 的函数节」默认 obj 在场；未写 ①缺失时是否单单元重编 ②重编必须用 match 的 hypothesis flags（见 1.1 flags 陷阱）③重编耗时（wine 单单元约 1s 级，compare 全量 128 单元则分钟级——fdiff 的提示是"重跑整场 match"，对单地址查询过重）。
- **addr→(unit, symbol) 映射现成但 spec 未提**：`data/status/pal3_registry.jsonl`（写入 `pipeline/compare_pal3.py:844-849`，含 `addr/name/file/status/match_pct/size`）——first_diff CLI 按 addr 查询必须经它（或 detail），spec §1.2 接口只给了 `<addr>`，没写解析链。

### 1.5 范围与序：spec 序 vs handoff 2→3→1；TDD/判据可执行吗

- **序不一致（实证）**：
  - handoff：`data/status/progress_handoff_20261105.md:31-33`——「①first_diff ②progress ③asm-differ …… **序：2→3→1**（first_diff 零成本即用）」⇒ ②progress → ③asm → ①first_diff。
  - spec：`docs/specs/2026-11-05-l1-diagnosis-tools-design.md:14-44` 按 1.1 progress → 1.2 first_diff → 1.3 asm_diff = **2→1→3**，且 §1 标题自称"按落地序"（spec:14）。
  - ⇒ **不一致，且 spec 未写偏离理由**。两种序各有道理（spec 序让 first_diff/asm_diff 共享 byte_source 先落地），但必须显式声明"偏离 handoff 序，理由 X"，否则 handoff 是立项文件、spec 是落地文件，两处序会各自被执行者引用。
- **TDD 每步可测性**（spec:54-61）：
  1. byte_source 装载测：**原字节锚可测**（PAL3.exe 稳定）；**编译侧锚依赖易失 obj**（1.4）⇒ 需改为"obj 在场才跑 / 或入库 fixture"。
  2. match_progress 合成夹具测：可测 ✓；**真数据 215 行可测** ✓（census total=215 实测），但"总和对账"必须按 1.2 修键名与单源。
  3. first_diff CLI「对已知 partial 地址给出非 None 首差」：**判据过弱**——实测 detail 541 行 `first_diff` **全部非 None**（其中 221 行 =0），**读 JSON 即可通过**，测不出工具是否真装载/真比对。建议改为"重算值 == detail 存值（抽样 N 行）"。
  4. asm_diff「首分歧标记正确」：**缺 oracle**；可用 `detail.first_diff` 的字节 offset 落在首分歧指令 span 内作断言（`tools/byte_diff_explain.py:141` 已有 span 判定写法可抄）。
  5. 「预存 7 失败零新增」：**实证** `.superpowers/sdd/2026-11-04-converter-proof-impl-plan/final-suite.log:198` = `7 failed, 1102 passed, 355 skipped` ✓；handoff:38 同述 ✓。
- **验证判据（spec:63-69）可执行性**：除 "L1 总和 = s4_baseline **matched**"（同 1.2，键名歧义）外，其余（样例报告落盘、双侧指令列、测试全绿）均可执行。
- **gate.sh 断言（spec:61）**：仓内 `gate.sh` 只有 `ghidra_track/gate.sh`（触发面=转换器/证明器 9 件，见 `.git/hooks/pre-commit`→`pipeline/hooks/pre-commit:6-9`），且 pre-commit 主体只跑 `pipeline/cli.py check`（`pipeline/hooks/pre-commit:12`）**不跑 pytest** ⇒ "gate.sh 不涉本层"**字面成立**；但新测试的实际入口是 SDD suite / 手工 pytest，spec 未写这条路径。

### 1.6 替代方案：partial 行是否已含首差信息（该不该缩 scope）

**结论：已含——first_diff 的"首差 offset"部分几乎是零增量，建议缩 scope / 改为薄 CLI。**

- `pipeline/compare_pal3.py:659-665` 每条 partial 行已写：`first_diff`（`:662`，取自 `tools/gbengine_compare.py:402` `diffs[0]`）、`diffs[:64]`（`:665`）、`n_diff`、`compiled_len`、`size`、`obj` 路径、`sem_reg/sem_real/semantic_match`、`reloc_skipped`。
  - **语义要点**：`diffs` 已跳过 reloc 字节（`tools/gbengine_compare.py:360-367`，`elif i in relocs: matches += 1`）且只在 `min_len` 内扫（`:360`）⇒ **存下来的 `first_diff` 是"reloc-aware + min_len 内"的**。
  - ⇒ spec:35 的纯函数 `first_diff(orig, comp) -> int|None`（两参、无 reloc）**语义与存值不同**：naive 版会把 reloc 4 字节差异当首差（可能比存值更早），且"长度不齐但 min_len 内全同"时存值为 None 而 naive 可能返回越界/None 各说各话。**纯函数签名必须带 `relocs` 并 pin 到 compare_bytes 语义**，否则工具读数与棘轮判据分叉。
- 既有 CLI：`tools/fdiff.py`（按 unit+函数名查，双侧 hex+反汇编+`<>` 标注，实测跑通）；批量：`tools/byte_diff_explain.py`（对齐+首分歧+原因族，输出 2026-10-08 陈旧件）。
- **first_diff.py 的净增量**（值得做的部分）：
  1. **按 addr 查询**（fdiff 只认 unit+名字；detail 里也没有 L1 函数的行）；
  2. **detail 陈旧/缺行时现场重算**（需 obj + flags，见 1.1/1.4）；
  3. **两侧 N 字节 hex 窗口 + 一行反汇编**的固定输出形（fdiff 有 hex+反汇编但无"首差窗口"聚焦）；
  4. 并入 byte_source 单源（收敛现存 3 份 .text 解析）。
- **asm_diff.py 的净增量**：把 byte_diff_explain 的 `disasm/key/SequenceMatcher/classify` 抽成 per-addr CLI（fdiff 是偏移对齐，插删后错位——实测可见）；**不是**从零写 200 行。

---

## 2. 修订建议（可操作，按优先级）

**P0（不改则判据/工具会假绿或假红）**

1. **对账断言改单源 + 精确键名**（spec:27、:66）：
   - 写死：`sum(表中 L1 列) == data/status/s4_baseline.json 的 stats.match_L1`；
   - **partial 列也取自同一文件的 `rows`（status=='partial'）**，禁止取 `s4_diff_detail`（两文件已实证不同源，见 1.2）；detail 只用于取 diffs/first_diff 明细；
   - 聚合前加**同源校验**：`detail.l1 == baseline.stats.match_L1` 且 `detail.partial == baseline.stats.partial`，不等则 **fail-loud 打印"两文件非同 run（差 X/Y），拒绝聚合"**（复用 spec:73 的 fail-loud 纪律）；
   - 定义第三种行 `out_of_range` 与"无基线单元"（census ok 但 baseline 无行，实测 6 个）的状态列语义，禁止静默丢弃。
2. **补 obj 生命周期与 flags 章节**（spec:33-34、:50）：
   - 写明 obj 路径 `/tmp/pal3_probe/s4_<md5>[:8].obj`（`probe_compile.py:40-41`）与**每次 probe 即清空**（`probe_compile.py:300`）；
   - 缺失回退 = **单单元重编**，flags 必须用 `pipeline/cli.py:737` 的 hypothesis 串（或直接读 `s4_baseline.json.flags`），并断言与 detail.flags 一致；
   - 明确 addr→(unit,symbol) 经 `data/status/pal3_registry.jsonl`（`compare_pal3.py:844-849`）。
3. **纯函数 `first_diff` 签名 pin 语义**（spec:35）：`first_diff(orig, comp, relocs=frozenset()) -> int|None`，规则与 `tools/gbengine_compare.py:360-402` 逐条一致（reloc 字节不计、只扫 `min_len`、长度不齐但 min_len 全同 ⇒ None + 显式 `len_mismatch` 标志）；单测加"reloc 前置差异"用例（spec:56-57 现有用例覆盖不到）。

**P1（序与复用面）**

4. **序**：要么改 spec §1 顺序为 2→3→1 对齐 handoff（`progress_handoff_20261105.md:33`），要么在 spec:14 加一句"偏离 handoff 序：2→1→3，理由=first_diff/asm_diff 共享 byte_source 先落地"。二选一，不可两处各说。
5. **复用面重写**（spec:37-44、:46-52）：
   - asm_diff 的反汇编/对齐/首分歧**从 `tools/byte_diff_explain.py` 抽取**（`:65-75` disasm、`:78-79` key、`:148` SequenceMatcher、`:152-163` 首分歧、`:82-112` classify），反汇编器用 **capstone（5.0.7 实测在位）**，去掉 spec:34 的 objdump 首选（spec:73 自己已列 objdump 脆弱风险）；
   - byte_source 改为**收敛**现存 3 份 `.text` 解析（`compare_pal3.py:76` / `byte_diff_explain.py:46` / `gbengine_compare.py:36`），通用 VA→file offset 优先直接复用 `tools/compare_exe.py:102-131` 的 `PEParser`；
   - §0 措辞更正（spec:5）：删"无工具面/靠人肉对字节"，改为"已有 fdiff（单函数）与 byte_diff_explain（批量）但缺 addr 键查询/进度仪表/新鲜度保障"。
6. **缩 scope 建议**：`first_diff.py` = fdiff 内核 + addr/registry 入口 + 首差窗口聚焦（预计 <150 行）；`asm_diff.py` = byte_diff_explain 的 align/classify 抽成 per-addr CLI（预计 <100 行）；两者共用 byte_source。**不建议**并行新写两套装载与反汇编。

**P2（判据可执行性）**

7. spec:67「first_diff 对已知 partial 地址给出非 None 首差」→ 改为"抽样 K 行，工具重算 `first_diff` == `s4_diff_detail` 存值，且 hex 窗口含该 offset"（现判据读 JSON 即过，无判别力）。
8. spec:68「首分歧标记正确」→ 加 oracle：首分歧指令的字节 span 覆盖 `detail.first_diff`（span 写法抄 `byte_diff_explain.py:141`）。
9. spec:56-58 装载测的编译侧锚 → 改"obj 在场才断言，缺失时 skip 并打印原因"（或把 1 个小 obj 入 `tests/fixtures/`）。
10. spec:61 补一句新测试的真实入口（SDD suite / `python3 -m pytest tests`），gate.sh 断言保留（已核：`ghidra_track/gate.sh` 触发面仅转换器 9 件）。

---

## 3. 与任务背景数字的对照（防引用错账）

| 背景给定 | 实测 | 裁定 |
|---|---|---|
| L1 棘轮 94/957 | `s4_baseline.stats` = **match_L1 161 / matched 924 / rows 851**；`cli.py status` 打印「L1 棘轮=161」 | **对不上，来源未复验**（94/957 未在 status 数据文件中检索到；引用前须重新核） |
| 541 partial 行 / 116 单元 | `s4_diff_detail` = **541 行 / 116 单元** ✓ | 一致 |
| compare_pal3 + gbengine_compare = 现有字节比对件 | ✓（`compare_pal3.py:40` import gc；`parse_coff_obj`/`compare_bytes` 复用） | 一致 |
| probe_census = S2 per-unit | ✓（`s2.results` 每项 `unit/status/errors[]`，实测 ok 项 errors=[]、fail 项 errors 含 code） | 一致；另注意 error 根因族文件是 `data/status/error_classification.json`（87 文件级 `dominant_category`，mtime **2026-11-02**，比 census 陈旧） |
| oot 三件为借鉴源 | `progress_handoff_20261105.md:31-33` ✓ | 一致（但序不同，见 1.5） |

---

## 4. 六条必攻 · 一句话裁定表

| # | 必攻问题 | 裁定 |
|---|---|---|
| 1 | 装载面形 / 复用假设成立吗 / PE 解析查没查 | **成立、成本未低估**（fdiff 先例实测跑通）；但漏 flags 复用（`cli.py:737` vs `compare_pal3.py:429`），且**现成通用 PE 解析存在**（`compare_exe.py:102-131`）spec 没点名；仓内已有 3 份 .text 解析，byte_source 应收敛而非新增第 4 份 |
| 2 | L1 总和=s4 matched 在 partial 语义下成立吗 | **字面不成立**（matched=924 含 73 无行符号）；同 run 内 status 互斥自洽（851=161+690），但 **baseline(161/690) 与 detail(110/542) 已实证不同源**、44 个函数状态相反/缺失 ⇒ 必须单源 + 同源校验 |
| 3 | 自建 200 行有依据吗 / 有更省既有件吗 | 量级**有旁证**（byte_diff_explain 201 行全覆盖）；**更省既有件=有且就是它**（SequenceMatcher 对齐+{T}/{R} 归一+首分歧+分类，capstone 5.0.7 在位）；objdump 首选与仓内面分叉 |
| 4 | obj 在哪 / 生命周期盲区 | **盲区确认**：`/tmp/pal3_probe`，`probe_compile.py:300` 每次 probe 清空；spec 未提缺失回退/flags/addr 解析链；现 128 obj mtime 11-03，与 detail(11-04) 非同刻（成因未复验） |
| 5 | 序一致吗 / TDD 可测吗 / 判据可执行吗 | 序**不一致**（handoff 2→3→1 vs spec 2→1→3，未声明）；TDD 步 1/3/4 判据需加固（步 3 现判据无判别力）；预存 7 失败**实证**；gate.sh 断言字面成立但非 pytest 入口 |
| 6 | partial 行已含首差吗 / 该缩 scope 吗 | **已含**（`first_diff/diffs/obj/compiled_len` 全在行内）+ fdiff/byte_diff_explain 两件在场 ⇒ first_diff 缩为"addr 键 + 重算 + 窗口聚焦"薄 CLI，asm_diff 改为抽取既有 align/classify，不从零写 |

---

## 5. 未复验（不判定清单）

1. **baseline/detail 不同源的成因**：推断为 ratchet 退化回写（`pipeline/cli.py:729,793-794`）或跨 run 落盘，**未**用 git/运行日志证实（两文件 git 最后提交分别为 `6e3d8637f 2026-10-30`、`a85c4ad06 2026-11-03`，与 mtime 11-04 10:04 亦不吻合，成因保留）。
2. **背景数字 94/957** 来源未找到（status 数据文件检索无果）；当前权威读数为 L1=161（`cli.py status`）。
3. **测试套件当前态**：仅核到 `final-suite.log:198` 的历史 `7 failed, 1102 passed`（2026-11-04）；本次**未**重跑全量 pytest。
4. **obj 与 detail 是否同 run**：obj mtime 11-03 20:29 vs detail 11-04 10:04，不吻合；是否由重编失败/复用旧 obj 造成未验证。
5. **`tools/byte_diff_explain.py` 当前可用性**：只读了源码（其输出 `s4_diff_explain.json` 为 2026-10-08 陈旧件）；**未**执行（它会覆盖盘面产物，复核不写盘）。
6. **wine 单单元重编耗时**：未实测（仅由 `probe_census.s2.results[].secs` 见到 0.76s~22.92s 的编译耗时分布，非 match flags）。
7. **asm-differ 上游 x86 支持度**：维持 spec 原判「未验=不判定」（spec:11-12、:39 一致，无需改）。
