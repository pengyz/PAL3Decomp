# L1 诊断工具层设计 v2（oot 借鉴三件）——2026-11-05

> v1→v2（对抗复核 review_l1_tools_spec_20261105 三硬伤+事实纠偏全收编）：
> ①对账断言改同源 fail-loud ②obj 生命周期+match flags 盲区补 ③序偏离显式声明
> ④「无工具面」纠偏=**fdiff/byte_diff_explain 既有**·本设计=整合+补 progress。

## 0. 目标与边界（v2 纠偏）

**事实基线（复核实测）**：`tools/fdiff.py`（单函数双侧 hex+capstone 反汇编·实测跑通·
capstone 5.0.7 在位）+ `tools/byte_diff_explain.py`（SequenceMatcher 对齐·call/jmp 目标
归一 {T}·reloc 归一 {R}·首分歧抽取）**已覆盖诊断大半**——v1「无工具面/靠人肉」不成立。
L1 权威读数=**161**（cli.py status·v1 误写 94/957=陈旧题注值）。

**目标（v2）**：整合既有诊断件 + 补进度作战图 + 补同源校验（防读数自欺）。

**非目标**：permuter（下期）· asm-differ 上游引入（x86 未验=不判定维持）· 多版本。

## 1. 组件（三件·序=2→1→3·偏离 handoff 2→3→1 显式声明）

**序偏离理由**：progress 零新依赖先行；first_diff 数据已在 detail（薄件）；asm=整合
较重放后。handoff 序写于 fdiff 既有性发现之前——以本 spec 为准（记账）。

### 1.1 `tools/match_progress.py`（先做·聚合+同源校验）

**输入**：`s4_baseline.json`（**唯一 L1/partial 权威**）· `probe_census.json` ·
`error_classifier` 输出 · `pal3_registry.jsonl`（addr→unit/symbol）。
**同源校验（fail-loud·复核硬伤①）**：`s4_diff_detail.l1 == s4_baseline.stats.match_L1`
（复核实证两文件不同源：baseline match_L1=161 vs detail l1=110·1 函数状态相反——
疑棘轮回写旧 baseline 而 detail 无联动，成因未复验）⇒ 不等即 exit 1 报「不同源禁聚合」。
**对账断言（键名写死）**：表 L1 列总和 == `s4_baseline.stats.match_L1`（禁用 stats.matched
——其含 73 unresolved_synth 无 status 行，compare_pal3.py:479/491-493）。
**输出**：`data/status/match_progress.json`+表（unit|S2|L1|partial|错误|根因族）按 partial 降序。

### 1.2 `tools/first_diff.py`（薄 CLI·复核缩编）

**复核纠偏**：partial 行**已含** `first_diff/diffs[:64]/obj/compiled_len`
（compare_pal3.py:659-665）⇒ 本件=「addr 键查找+窗口聚焦+缺失时重算」薄层，非新比对引擎。
- addr→unit/symbol：`pal3_registry.jsonl`（compare_pal3.py:844-849 同源）
- **obj 生命周期（复核硬伤②）**：obj 在 `/tmp/pal3_probe` 且 probe 结束 rmtree
  （probe_compile.py:40-41/300）⇒ detail 有存值→直接展示（零依赖）；需重算→
  提示先跑 probe 或按 match 同款 **hypothesis flags**（cli.py:737·禁 compare_pal3 缺省
  PROBE_FLAGS——否则假首差）
- 纯函数 `window(hay: bytes, needle: bytes, n) -> tuple` 仅管窗口（比对语义=
  gbengine_compare 既有 reloc-aware/min_len 形，**不另造签名**——复核③收编）

### 1.3 `tools/asm_diff.py`（整合既有·非新建 200 行）

**复核纠偏**：抽取整合 `fdiff.py`（双侧反汇编）+ `byte_diff_explain.py`（对齐/归一/首分歧）
→ `align_disasm(orig, comp) -> pairs`（复用其 SequenceMatcher+{T}/{R} 归一逻辑——
**import 复用禁复制**·TOS 单源）；`asm_diff.py` CLI=两件的编排+三态标记输出。
**byte_source 收敛（复核④）**：仓内已有 3 份 .text 解析+现成通用 PE VA→file offset
（tools/compare_exe.py:102-131）+`from compare_pal3 import exe_text_image` 先例
（fdiff.py）⇒ **不建第 4 份**——新代码只 import 既有，缺的仅「编译侧取数」一处收敛。

## 2. TDD 序（v2 修）

1. **progress**：合成 baseline+detail 夹具（含**不同源反例**=l1 不等必红）→ 真数据跑=
   同源校验过+L1 总和==stats.match_L1 断言
2. **first_diff 薄层**：detail 存值路径（addr→行→窗口展示）+缺 obj 提示路径；
   反例钉：detail 首差=0 的行展示 0（非「非 None」——v1 判别力缺陷修）
3. **asm_diff**：align_disasm 合成序列测（复用件接线正确性）+真地址跑 fdiff 整合输出
4. 全套件回归（预存 7 零新增·实证 final-suite.log:198）

## 3. 验证判据（v2）

- 三工具真实数据样例报告落 `data/status/`
- progress 同源校验对**当前真实文件**过（或 fail-loud 报不同源=本身即发现）
- first_diff 对 detail 真 partial 行出窗口展示
- asm_diff 对真地址出三态标记列
- 新增≥8 测全绿·预存 7 零新增

## 4. 风险（v2 增）

- **s4 两文件不同源成因未复验**（疑棘轮回写）——progress 只校验不修源；修源=另案
- 重编路径依赖 wine+flags 一致性 → 重算路径显式提示 flags 来源，缺则拒算（禁假首差）
- byte_diff_explain/fdiff 未执行过（复核只读码）→ 接线首跑即验证
