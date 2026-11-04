# 转换器完备性与正确性证明——实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 B 转换链（annotation→plan→changeset→Ghidra）建成三件套证明（矩阵+回读对账+独立 oracle fixture）+mutation 自证，门禁化后重看 B 面现状。

**Architecture:** 纯函数核心（独立投影/diff/归一）与 daemon 回读壳分离；证明器**禁止 import 转换器模块**（假绿根防）；语料键扫描驱动矩阵；mutation 注入证证明器自身有效。

**Tech Stack:** Python 3.10 · pytest · ghidra-mcp daemon（MCP JSON-RPC）· mingw CMake（fixture 编译面可选）

**Spec:** docs/specs/2026-11-04-converter-proof-design.md（v2·R1-R10 已收编——计划从 spec 辩证，两件同行）

## Global Constraints

- **verify 域禁 import**：verify_core/verify_b_import/proof_matrix/mutation_proof/fixture_proof 不得 import gen_plan/import_annotation/plan_to_changeset/import_standard（R1 铁则；任务 3 有 import 禁令测试）
- TDD：每任务红→绿→commit；R15 纯函数先行
- 地址归一必须切片 `a[2:] if a.startswith('0x') else a`，**禁 `lstrip('0x')`**（前导零陷阱三犯记）
- 标准数据通路：只经 ghidra-mcp daemon 工具面/apply_changeset，禁旁路（防旁路三纪律）
- 归并 tie-break（spec §3）：owner 优先 > adjudication='confirmed' > sorted 类名序 > 首个
- 所有 fail-loud：fail>0 未入分账=红（R10）

## Review Focus

1. **假绿（共享 bug 双侧一致）**：verify 域 import 转换器模块 ⇒ 共享解析 bug 使 diff=∅ 假绿——Task 3 有「import 禁令」测试（importlib 扫描 verify 模块的依赖）+ Task 6 mutation「调换多注胜者」类必须抓红
2. **extra 恒红**：B 侧自动分析产物（未认领函数/AUTO 名）涌入 extra ⇒ 证明永远 BROKEN——Task 3 `norm_facts` 的 extra 域过滤测试（AUTO_/FUN_ 前缀名不计入）
3. **确定性漂移**：gen_plan glob 未排序 ⇒ 多注胜者随机器序漂移 ⇒ 同输入两次 plan 不同——Task 2 重复运行一致性测试
4. **同址函数+全局 key 互吃**：plan_to_changeset 的 `'name:'+addr` 键空间比 Changeset targetKey 粗 ⇒ 全局改名吃掉函数改名——Task 2 targetKey 分立测试（同址既有函数又有全局时两个 rename op 都保留）
5. **导入 fail 静默**：import_standard 只计数不 fail-loud（实测 24 条「No transaction is open」）——Task 7 的 fail 分账测试（fail>0 且未入分账 ⇒ exit 1）

---

### Task 1: 变体键发明偏移 bug 修复（RED-0）

**Files:**
- Modify: `ghidra_track/import_annotation.py:59`（int() 错位病灶）
- Test: `tests/test_variant_key.py`

**Interfaces:**
- Consumes: 无（独立首轮）
- Produces: `parse_variant_key(key: str) -> int | str`（import_annotation.py 内；变体键 `'144_1'` → `'144_1'` 保留或显式偏移表查——禁 int() 吞）

- [ ] **Step 1: 写失败测试**（真值锚：PalScript.json:659,666 `'144_1'`/SceneMgr.json:138）

```python
def test_variant_key_not_int_coerced():
    # '144_1' 不得变 1441（发明偏移）；'50814_0' 不得变 508140
    assert parse_variant_key('144_1') != 1441
    assert parse_variant_key('50814_0') != 508140
def test_plain_offset_key_passes():
    assert parse_variant_key('448') == 448
```

- [ ] **Step 2: 跑测确认红**：`pytest tests/test_variant_key.py -v` ⇒ FAIL（ImportError 或断言败）
- [ ] **Step 3: 实现 `parse_variant_key`**：十进制纯数字形才 int()；含 `_`/非数字=原样返回并在下游显式处理（禁发明偏移）
- [ ] **Step 4: 跑测绿 + 全既有回归**：`pytest tests/ -q -x --ignore=tests/test_debt_recovery_pure.py`（收案错的 test_audit_callsite_evidence 除外）
- [ ] **Step 5: Commit**：`fix(b-import): 变体键 int() 发明偏移修复（144_1→1441 实锤）`

### Task 2: 归并确定性 + targetKey 对齐

**Files:**
- Modify: `ghidra_track/gen_plan.py:17`（glob→sorted glob）· `ghidra_track/import_annotation.py:38-81`（build_import_plan 归并段）
- Modify: `ghidra_track/plan_to_changeset.py`（key 空间分立）
- Test: `tests/test_plan_determinism.py`

**Interfaces:**
- Produces: `build_import_plan(ann_dir) -> list[dict]` 保证同输入逐字节同输出；plan_to_changeset 同址函数+全局产出**两个** op（`rename_function`+`rename_global` 各带 targetKey 语义）

- [ ] **Step 1: 失败测试**

```python
def test_plan_deterministic():
    a = build_import_plan('ghidra_track/fixture/cases/case-01-struct-union-overload/annotations')
    b = build_import_plan('ghidra_track/fixture/cases/case-01-struct-union-overload/annotations')
    assert a == b, '同输入两次 plan 必须逐字节同（glob 序/归并序确定性）'
def test_same_addr_fn_and_global_both_kept():
    plan = [{'kind': 'set_name', 'addr': '0x401000', 'name': 'Fn'}, {'kind': 'define_global', 'addr': '0x401000', 'name': 'g_X'}]
    ops = [o for b in plan_to_changesets(plan) for o in b['ops']]
    kinds = sorted(o['op'] for o in ops)
    assert kinds == ['rename_function', 'rename_global'], 'targetKey 分立：同址两 op 都保留（现互吃）'
def test_multiclaim_tiebreak():
    # owner 优先 > confirmed > sorted 类名序（对齐 apply_annotations.py:1382-1385）
    ann = {'A_cls.json': {'name': 'Z_cls', 'methods': {'0x401000': {'name': 'fromZ'}}},
           'B_cls.json': {'name': 'A_cls', 'methods': {'0x401000': {'name': 'fromA', 'owner': 'A_cls'}}}}
    merged = merge_method_claims(ann)   # build_import_plan 内归并段抽出的可测函数
    assert merged['0x401000']['name'] == 'fromA', 'owner 优先胜出'
    ann2 = {'A.json': {'name': 'Z_cls', 'methods': {'0x401000': {'name': 'z', 'adjudication': 'confirmed'}}},
            'B.json': {'name': 'A_cls', 'methods': {'0x401000': {'name': 'a'}}}}
    assert merge_method_claims(ann2)['0x401000']['name'] == 'z', 'confirmed 优先于类名序'
```

- [ ] **Step 2: 确认红**（`pytest tests/test_plan_determinism.py -v`）
- [ ] **Step 3: 实现**：glob 加 sorted（gen_plan.py:17）；build_import_plan 归并段按 tie-break 排序遍历；plan_to_changeset key 改 `fn-name:`/`global-name:` 分立
- [ ] **Step 4: 绿 + 回归**：`pytest tests/test_plan_determinism.py tests/test_plan_to_changeset.py -q`
- [ ] **Step 5: Commit**：`fix(b-import): 归并确定性（sorted+tie-break）+ targetKey 分立`

### Task 3: 纯函数核心（独立投影/diff/归一）

**Files:**
- Create: `ghidra_track/verify_core.py`
- Test: `tests/test_verify_core.py`

**Interfaces:**
- Produces（后续任务依赖的精确签名）:
  - `norm_addr(s: str) -> int`
  - `norm_facts(facts: dict) -> dict`（extra 域过滤：`FUN_`/`AUTO_`/`thunk_` 前缀名不计 extra）
  - `project_ann_facts(ann_dir: str) -> dict` — **独立实现**解析与归并（禁 import 转换器；tie-break 同 Task 2）
  - `diff_facts(expected: dict, actual: dict) -> dict` → `{'match': [...], 'missing': [...], 'changed': [...], 'extra': [...], 'unverifiable': [...]}`，每项 `{'path': str, 'expected': Any, 'actual': Any, 'reason': str|None}`
  - 事实形（canonical）：`{'functions': {addr_int: {'name','signature','class','adjudication'}}, 'structs': {name: {'size','members': {offset_int: {'name','type'}}}}, 'globals': {addr_int: {'name','type'}}, 'skips': {addr_int: {'kind'}}}`

- [ ] **Step 1: 失败测试**（含假绿反例钉）

```python
def test_norm_addr_no_lstrip_trap():
    assert norm_addr('0x00523b90') == 0x523b90
def test_extra_filtered():
    d = diff_facts({}, {'functions': {1: {'name': 'FUN_00400001'}}})
    assert d['extra'] == [], '自动名不计 extra（否则恒红）'
def test_diff_catches_rename():
    ...
def test_diff_catches_offset_shift():
    ...
def test_adjudication_winner_semantics():
    # 同址双认领：expected 侧取 confirmed 胜者；actual 若为败者名 ⇒ changed
    ...
def test_verify_core_has_no_converter_imports():
    import ast, pathlib
    src = pathlib.Path('ghidra_track/verify_core.py').read_text()
    tree = ast.parse(src)
    for node in ast.walk(tree):
        if isinstance(node, ast.ImportFrom):
            assert not any(m in (node.module or '') for m in ('gen_plan', 'import_annotation', 'plan_to_changeset', 'import_standard')), 'R1 铁则：禁 import 转换器'
```

- [ ] **Step 2: 确认红**
- [ ] **Step 3: 实现 verify_core.py**（纯 stdlib；解析独立于 import_annotation 的实现，规则与 apply_annotations.py:1382-1385 对齐但代码独立）
- [ ] **Step 4: 绿 + 回归**
- [ ] **Step 5: Commit**：`feat(b-proof): verify_core 纯函数核（独立投影/diff/归一+import 禁令钉）`

### Task 4: daemon 回读壳 + verify CLI

**Files:**
- Create: `ghidra_track/verify_b_import.py`
- Test: `tests/test_project_b_facts.py`（mock daemon 层）

**Interfaces:**
- Consumes: Task 3 的 `project_ann_facts`/`diff_facts`/`norm_facts`；`ghidra_track/import_via_daemon.py` 的 `rpc/notify/tool`（传输层复用=标准通路）
- Produces: `project_b_facts(tool, S: dict) -> dict`（回读面：`list_functions`/`get_function_info`/`list_data_types`/`get_data_type`/`get_global_variables`——正名见 spec §2）；CLI `python3 ghidra_track/verify_b_import.py --ann <dir> --gpr <path>` → `data/status/b_import_proof_<date>.json` `{coverage, diffs, verdict}`

- [ ] **Step 1: 失败测试**（mock tool 返回样例 facts，断言投影形+verdict 计算；含 unverifiable 二分：evidence/name_source → 载体注释或 dropped+理由，无理由=红）
- [ ] **Step 2: 确认红**
- [ ] **Step 3: 实现**（project_b_facts 经 daemon 工具回读→canonical facts；CLI 串 Task 3 diff；verdict：diff 空+无无理由 unverifiable+导入分账全 ⇒ PROVEN，否则 BROKEN；DROPPED 态=矩阵 dropped 全显式时）
- [ ] **Step 4: 绿**（mock 测）+ 活体烟测（任一 session 跑通出报告=不要求 PROVEN）
- [ ] **Step 5: Commit**：`feat(b-proof): verify_b_import 回读壳+CLI（unverifiable 二分）`

### Task 5: 矩阵语料扫描器

**Files:**
- Create: `ghidra_track/proof_matrix.py` · `ghidra_track/proof_matrix.json`（分类账）
- Test: `tests/test_proof_matrix.py`

**Interfaces:**
- Produces: `scan_corpus_keys(ann_dir) -> dict[str, int]`（机械键扫描：struct 顶层/成员/methods/functions/globals 全键路径+计数——复核实测 45/14/33/17/15 种键域）；`build_matrix(ann_dir, dispositions: dict) -> dict`；测试断言：**扫描出的每个键路径在矩阵有条目**（无条目=红）

- [ ] **Step 1: 失败测试**（scan 对 fixture 语料出键集；矩阵缺条目时 build_matrix 报缺）
- [ ] **Step 2: 确认红**
- [ ] **Step 3: 实现**（键路径枚举器+disposition 分类账 schema `{key_path: {transfer: 'op'|'dropped', reason: str, verify: 'direct'|'indirect:<效果>'|'comment'|'none'}}`；人工填 disposition——首版含 spec §4 缺口表全条目）
- [ ] **Step 4: 绿**（对 data/annotations 真语料跑 scan=全键有条目）
- [ ] **Step 5: Commit**：`feat(b-proof): 矩阵语料扫描器+disposition 分类账`

### Task 6: mutation 自证（证明器有效性门）

**Files:**
- Create: `ghidra_track/mutation_proof.py`
- Test: `tests/test_mutation_proof.py`

**Interfaces:**
- Consumes: Task 3 `diff_facts`
- Produces: `MUTATIONS: list[(name, fn)]`——6 类：改名/移偏移/换型/删字段/多字段/**调换多注胜者**；`run_mutation_suite() -> report`——每类注入后 diff 必须非空（逐类断言红）

- [ ] **Step 1: 失败测试**（对合成 facts 跑 6 类注入，断言每类 diff 抓到；先以「胜者调换」类=复核最大假绿风险件为必测）
- [ ] **Step 2: 确认红**
- [ ] **Step 3: 实现**（注入器+报告；门语义：任一类未抓红 ⇒ suite FAIL）
- [ ] **Step 4: 绿**（6/6 抓红）——**mutation 不绿不得进 Task 7**
- [ ] **Step 5: Commit**：`feat(b-proof): mutation 自证 6 类（证明器有效性门）`

### Task 7: 转换器缺口修（spec §4 全表·六缺口）

**Files:**
- Modify: `ghidra_track/gen_plan.py:23-25`（adjudication 过滤+prefer）· `ghidra_track/plan_to_changeset.py:22-24`（set_global_type op）· `ghidra_track/import_annotation.py`（skip/墓碑消费·inline-struct dict 处置·owner 转）· `ghidra_track/import_standard.py:66-68`（fail-loud）
- Test: `tests/test_converter_gaps.py`

**Interfaces:**
- Produces: gen_plan 跳 `adjudication=='rejected'`+tie-break prefer；plan_to_changeset 产 `set_global_type` op；skip 语义转或 dropped+理由入矩阵；inline-struct dict 显式拒转+理由（禁静默降 byte）；**owner 转**（方法归属入 plan——effects 可验）；import_standard fail>0 未入分账 ⇒ exit 1

- [ ] **Step 1: 失败测试**（六缺口各一测：rejected 过滤/全局 type op/skip 分账/inline-struct 显式/owner 入 plan/fail-loud）
- [ ] **Step 2: 确认红**
- [ ] **Step 3: 逐缺口实现**（一缺口一 commit 子步；每个修完跑对应测）
- [ ] **Step 4: 全绿 + fixture 回归**
- [ ] **Step 5: Commit**：`fix(b-import): 转换器五缺口（adjudication/global-type/skip/inline-struct/fail-loud）`

### Task 8: case-02 fixture + 独立 oracle + fixture_proof

**Files:**
- Create: `ghidra_track/fixture/cases/case-02-missing-shapes/`（annotation 含嵌套 union/inline-struct dict/变体键/占位名/adjudication 对）
- Create: `ghidra_track/fixture/cases/case-02-missing-shapes/expected/facts_oracle.json`（**手写**独立 oracle，禁脚本生成）
- Create: `ghidra_track/fixture_proof.py`
- Test: `tests/test_fixture_proof.py`

**Interfaces:**
- Consumes: Task 3/4 全件
- Produces: `run_fixture(case_dir, gpr) -> report`——case-01+case-02 全链（gen_plan→import→回读）vs 独立 oracle 零差

- [ ] **Step 1: 手写 case-02 annotation+oracle**（人写 expected 文件；标注每期望行的来源）
- [ ] **Step 2: 失败测试**（run_fixture 断言零差——现必红=缺口未修完/投影不全）
- [ ] **Step 3: 实现 fixture_proof.py**（净室项目+daemon 会话流程；L-persist：关会话走优雅关禁 force）
- [ ] **Step 4: 绿**（case-01+02 双零差）
- [ ] **Step 5: Commit**：`feat(b-proof): case-02 缺形 fixture+独立 oracle+链跑器`

### Task 9: 门禁接线

**Files:**
- Create: `ghidra_track/gate.sh`
- Modify: `.git/hooks/pre-commit`（触发面段）· `docs/specs/2026-11-04-converter-proof-design.md`（§2 勘误补：hook 实路径）

**Interfaces:**
- Produces: 转换器 5 件（import_annotation/gen_plan/plan_to_changeset/import_standard/verify 自身）改动时 gate.sh 必跑 mutation+fixture 二证；红=exit 1

- [ ] **Step 1: 失败测试**（gate.sh 空跑 exit 0；人为改 gen_plan 触发面+注入坏 fixture ⇒ exit 1——shell 测入 pytest subprocess）
- [ ] **Step 2: 确认红**
- [ ] **Step 3: 实现**（gate.sh=mutation+fixture 串跑；pre-commit 钩子检测触发面路径命中则调 gate.sh；环境注记：daemon 互斥持库+端口 8432）
- [ ] **Step 4: 绿**（真触发一次全链）
- [ ] **Step 5: Commit**：`feat(b-proof): 门禁接线（gate.sh+pre-commit 触发面）`

### Task 10: B 面现状重看（终证读数）

**Files:**
- 无新件（全链跑+读数报告）
- Update: `data/status/b_status_reread_20261104.md`（现状账）

- [ ] **Step 1: 证明态确认**：`verify_b_import.py` 真实 session proof ∈ {PROVEN, DROPPED 全显式}
- [ ] **Step 2: 重灌+出码+整编**（被证明的转换器=读数可信）：净室导入→run.ts→mingw 整编——记录函数面/警告/错误桶（对照 25367 旧数）
- [ ] **Step 3: 现状报告落盘**（含「25367 三连不变」悬案的归因收口）
- [ ] **Step 4: Commit**：`chore(b-status): 被证明转换器重灌——B 面现状终读数`

---

## 任务间依赖

```
T1（变体键）┐
T2（确定性）┼─ T3（纯核心）→ T4（回读壳）→ T5（矩阵）→ T6（mutation 门）→ T7（缺口修）→ T8（fixture）→ T9（门禁）→ T10（现状）
            ┘                                      ↑ T5/T6 可与 T7 并行准备
```
T6 mutation 绿=硬闸：不绿不得进 T7。
