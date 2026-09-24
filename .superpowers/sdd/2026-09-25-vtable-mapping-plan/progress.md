# SDD ledger — plan: docs/superpowers/plans/2026-09-25-vtable-mapping-plan.md

## 飞行前冲突扫描

| 任务对 | 共享文件/接口 | 产出/消费 | 发现 |
|---|---|---|---|
| Task 1 ↔ Task 5 | `vtable_slot_order.py` | T1 产出正向规则，T5 消费做槽序校验 | ✅ 依赖明确（`vtable_decl_check.py:113` 实调 `match_key`） |
| ~~Task 2 ↔ Task 1~~ | ~~`vtable_slot_classifier.py`~~ | ~~T2 产出 kind，T1 消费做合成槽排除~~ | ❌ **假边（已更正，见下表注 M-1）**：T1 不 import T2 |
| Task 2 ↔ Task 3 | `vtable_slot_classifier.py` | T2 产出分类，T3 消费跳过合成槽 | ✅ 依赖明确（`vtable_sig_infer.py:102` 传**原始文本**） |
| Task 3 ↔ Task 5 | `methods_pending` | T3 产出候选签名，T5 消费做签名校验 | ✅ 依赖明确（`vtable_decl_check.py:134/:642`） |
| Task 4 ↔ Task 8 | `_layout_asserts.h` | T4 产出断言头，T8 验证编译 | ✅ 依赖明确 |
| Task 6 ↔ Task 8 | `vtable_verify.py` | T6 产出对比器，T8 做端到端 | ✅ 依赖明确 |
| ~~Task 7 ↔ Task 1~~ | ~~槽序规则~~ | ~~T7 转换需知道 slot→method 映射~~ | ❌ **假边（已更正，见下表注 M-1）**：stage3 不 import T1/2/3 |
| Task 2 ↔ Task 5 | `vtable_slot_classifier.py` | T2 产出分类，T5 消费 | ✅（更正时补记的真实边：`vtable_decl_check.py:122`） |
| Task 2 ↔ Task 6 | `vtable_slot_classifier.py` | T2 产出槽型词表，T6 消费 | ✅（更正时补记的真实边：`vtable_verify.py:119`） |

**表注 M-1（全分支最终评审 Minor-2 更正，2026-09-25 收口）**：原表两条边与代码不符 ——

* ~~「Task 2 ↔ Task 1：T2 产出 kind，T1 消费做合成槽排除」~~ **不成立**：`tools/vtable_slot_order.py`
  只 `import re` / `from dataclasses import dataclass, replace`（`:47-48`）；其 `kind` 是**声明侧**
  合成槽种类（虚析构 ⇒ `deleting_dtor`），而槽**内容**分类明确属 T2（该文件 `:33-34` 逐字如此分工）。
  ⇒ **T1 与 T2 之间没有依赖边**；T2 的真实消费者是 T3/T5/T6（见上表新增两行）。
* ~~「Task 7 ↔ Task 1：T7 转换需知道 slot→method 映射」~~ **不成立**：`pipeline/gen/stages/stage3_cleanup.py`
  只 `import hashlib/json/os/re/struct/sys` + `tree_sitter_cpp` + `from data import store`（`:7-17`），
  **不 import T1/T2/T3 任一**；其 `__vftable + N → obj->Method` 名称解析读的是**注解**
  `vtables[0].slots` + `methods`（`:184-187`），不经 T1 的槽序规则。
  ⇒ **T7 与 T1 之间没有依赖边**；T7 的输入是 IDA 注解（属注解层）。

| 任务 | 自洽性检查 | 发现 |
|---|---|---|
| Task 1 | 测试用金样本（vt6/DO、adv2、adv4）与规则一致 | ✅ |
| Task 2 | 测试覆盖 5 种 kind + composite，与识别特征表一致 | ✅ |
| Task 3 | 测试覆盖 5 种签名失败场景（C-1~C-6），与方法论一致 | ✅ |
| Task 4 | 测试覆盖 PMF 4/8/12 + offsetof 虚基跳过 | ✅ |
| Task 5 | 测试覆盖棘轮三态（升/平/降），与门禁规则一致 | ✅ |
| Task 6 | 测试覆盖符号归约/thunk 归一/强制发射 | ✅ |
| Task 7 | 测试覆盖三形态，与 stage3 扩展点一致 | ✅ |
| Task 8 | 测试覆盖 L1+.rdata 双裁判 | ✅ |

**扫描结论**：无冲突。所有任务间依赖明确，自洽性通过。

Ruling: 任务 1-8 可按序执行 — 无共享文件冲突，依赖链清晰 — 若发现隐藏冲突由评审循环捕获

## Task 1 实现者报告

状态：DONE_WITH_CONCERNS · 提交：4712eb9aa · 测试：35 passed / 0 failed

### 交付 API（供 Task 5/7 消费）
- `compute_slot_order(base_slots, local_decls)` → 单视图槽序
- `layout_local_segment(decls)` → 本地段打包（规则 3/4 核心）
- `compute_class_views(hierarchy, cls)` → MI 多视图
- `match_key(decl)` → 匹配键

### 顾虑（影响后续任务规则措辞）
1. **规则 4 精确语义**：合成槽为**单槽组**、组位由**声明序在各组首现序中的秩**决定、不参与同名分组（非字面声明下标）→ Task 5 校验文案必须用组秩语义
2. **打包细节**：本地段按**全部**本地声明（含覆写）打包（同名组逆序）**后**再摘除覆写者原位替换——摘除序≠重排序 → Task 5/7 共享打包逻辑必须照此
3. 虚继承视图合成 NotImplementedError（缺口归 Task 2/5/6）
4. pytest assertion rewrite 崩溃（环境问题，python3 直跑 35/35）
5. 补充金样本（P1/P2/P2b/D5-D9/DA/DB）不在既有 README，源自新探针

Ruling: 顾虑 1/2 改变 Task 5 规则措辞 — 记入台账，Task 5 分发时携带 — 若不修正会把正确槽序判死
Ruling: 顾虑 5 金样本出处 — 以 task-1-report.md 附录 A 为唯一出处，不合并 README — 保持单一出处避免漂移

## Task 1 评审结果

裁定 1（规格符合度）✅ · 裁定 2（任务质量）✅

### Important 发现（触发修复循环 R=1）
1. 【规格】简报规则 4 口径回写：合成槽=单槽组按声明秩定组位（非字面声明下标）→ 控制器回写简报 ✓
2. 【质量】金样本证据落盘：10 个补充样本需从 .gitignore 报告落盘到 `_vtable_abi_probe_20260925/` → 分发实现者修复

### Minor 发现（记入延期）
- test_a1/a2 编号与攻击 ID 互换（docstring 已注明）
- match_key 顶层 cv 对指针参数不剥离（实测影响低）
- layout_local_segment 仅测空输入
- TDD 红绿不可从 VCS 验证

Ruling: 简报口径回写为控制器职责 — 计划维护非代码修复 — 不触发实现者修复循环
Ruling: 金样本落盘为代码修复 — 分发实现者 R=1 — 恢复原实现者
Task 1: fix round 1/5 dispatched (gold sample persistence — syn_probe*.cpp → _vtable_abi_probe_20260925/)
Task 1: fix round 1/5 (1 addressed, 0 open — gold sample persistence; commits 4712eb9aa..40dacd759)

Ruling: 顾虑(a) 范围裁定 — 本发现项只要求补充样本落盘，不扩大到整目录入库 — 既有 9+ 源的跟踪状态是独立问题，不属本任务范围
Ruling: 顾虑(b) 原始输出入库 — 重编译+逐槽比对已证明可复现，测试 inline expected 已入库 — 原始输出不入库，保持轻量
Ruling: 顾虑(c) 纯新增 — 符合最小修复原则 ✓
Task 1: complete (commits ca3773606..40dacd759, 1 fix round, review clean)
  - deferred-minor: 金样本目录整体跟踪状态 + README"未跟踪草稿"措辞（交后续任务裁定）
  - deferred-minor: 报告附录 A 的 /tmp 依赖性措辞
Task 2: dispatched (synthetic slot classifier — binary observable forms, no mangling)

## Task 2 实现者报告

状态：DONE · 提交：97dc8161e · 测试：27 passed / 0 failed（Task 1 的 35 条回归全绿）

### 交付 API
- `classify_slot(SlotEvidence(...))` → `SlotClassification(kind, features, notes)`
- `needs_manual_review`（composite=True）
- `slot_order_kind()` / `normalize_kind()`（词面对接）
- kind 6 种：fn/deleting_dtor/adjustor_static/adjustor_vbase/purecall/composite

### 顾虑与裁定

Ruling: 词面冲突（Task1 'func' vs Task2 'fn'）— 规格用 'fn'，Task2 已提供 normalize_kind/slot_order_kind 互认适配器；Task 5/6 必须经适配器消费，Task 1 常量待下次触及该文件时统一为 'fn' — 若错：字符串比较 bug 会被 Task 5 集成测试捕获
Ruling: deleting_dtor 形态推断（表外扩展）保留 — 真实二进制 531 名仅 4 条 mangled，符号缺失时按表实现会静默误判为 fn；该推断仅在无符号证据时生效、留痕迹、不改变有符号样本结论，符合"工具生成候选，IDA 定性" — 若错：候选误判会被 IDA 定性环节拦截
Ruling: composite 只标记不定性 — B-4 动态 delta 不可归一二元组，Task 6 对比项用 (target, kind=dynamic, const) 三元组 — 记录进 Task 6 分发

## Task 2 评审结果

裁定 1（规格符合度）✅ · 裁定 2（任务质量）✅

### Important 发现（触发修复循环 R=1）
【质量】解析器"不认识的行静默丢弃" ⇒ fn + 零 notes，与"反静默误判"原则相悖。实测三例：
  ① objdump -dr 重定位注释行被当指令 ⇒ 真 adjustor 判成静默 fn
  ② IDA 地址列形态（CODE:00401000 / 00401000）整段丢弃 ⇒ insns 空 ⇒ fn
  ③ IDA 文本带 ; 注释 ⇒ 操作数解析成 other
修复要求：跳过 R_386_*/reloc 行、剥 ; 注释与地址列；即使不扩解析面，也必须在"输入非空但 insns 空/大量丢弃"时留"证据不足"痕迹

### Minor 发现（记入延期）
- is_external 是死参数（只用名字判 purecall）
- 符号判据是 brief 超集（??_G/??_E）——实为正确取舍，建议 docstring 写明 c2.obj 反例
- 两条自述"强判据"无可判别测试（冗余防御，建议补用例或降级措辞）
- 报告变异自述属实但 TDD 红绿不可从 VCS 验证
- 金样本 #5 符号归属不精确（形态对齐 #5 / 符号取自 c2）
- addr 字段只作诊断
Task 2: fix round 1/5 dispatched (parser silent failure — reloc lines / address columns / comments / insufficient-evidence trace)
Task 2: fix round 1/5 RETRY — 首次分发（静默失败，无产出）⇒ 重新分发聚焦版修复
Task 2: fix round 1/5 (1 addressed, 0 open — parser silent failure; commits 97dc8161e..53bc72b2f, 34 tests)
  修复：reloc 行跳过 / IDA 地址列剥离 / ; 注释剥离 / insufficient_evidence+partially_parsed 痕迹
  红相验证：HEAD 28 passed/6 failed → 修复后 34 passed

Ruling: 顾虑1（证据不足时 kind 仍 fn）— 保留 fn + notes 痕迹，Task 3 消费时必须检查 notes 非空，不得把 fn 当安全默认 — 若错：Task 3 会把证据不足的槽当普通函数
Ruling: 顾虑2-4（reloc 变体/地址列启发式/PE-COFF 不内联）— 按简报范围实现即可，变体退化均有痕迹不静默 — 若错：后续按需加正则
Task 2: complete (commits 40dacd759..53bc72b2f, 1 fix round, review clean)
  - deferred-minor: 50% 边界残留（既有，非本次引入）
  - deferred-minor: parse_disasm() 丢 ParseReport ⇒ 消费者须传原始文本（Task 3 契约钉死）
  - deferred-minor: insufficient_evidence 时 kind 仍 fn 且 needs_manual_review=False
  - deferred-minor: 发现项描述精度更正（例③ 实为 1 条误判 note，非零 notes）

Ruling: Task 3 契约 — 必须传原始 disasm 文本给 classify_slot/parse_disasm_report，禁止先 parse_disasm 再喂 Insn 元组 — 若错：证据不足痕迹失效，静默判 fn
Ruling: Task 3 消费 fn 时必须检查 notes 非空 — 不得把 fn 当安全默认 — 若错：证据不足的槽被当普通函数
Task 3: dispatched (signature candidate generator — BASE 53bc72b2f; 攻击用例 C-1~C-6 已转为测试要求; Ruling 1-6 已随分发携带)

## Task 3 实现者报告

状态：DONE_WITH_CONCERNS · 提交：fd2305f05（10 files, +3100）· 测试：新 58 passed / Task1 35 + Task2 34 全绿

### 交付 API（Task 5 消费）
- `SigEvidence` → `infer_signature`（合成槽返回 None=跳过）
- `infer_address_record`（一地址多候选）· `find_icf_groups` · `build_methods_pending`
- `iter_candidates` · `analyze_call_sites` · `param_class_equiv`
- methods_pending schema：键 `'0x%08X'` → {candidates:[...], icf_folded, ambiguous, skipped, conflicts}

### 发现项（跨任务 Critical，Task 2 文件范围）
**PE-COFF `dir32` 重定位行崩溃**（实测确认：`ValueError: invalid literal for int() with base 10: 'sg263'`；`R_386_32` 正常但真实 PE-COFF objdump 用 `dir32`）
⇒ 真实二进制凡字符串地址压栈函数都命中 ⇒ 所有消费者崩溃

Ruling: 开 Task 2 修复轮 R=2 — Critical 崩溃 bug + 承重（Task 5/6 会消费）+ 修复小（一行正则分支） — 若错：Task 3 的 sanitize 防御仍生效，无实际损失
Ruling: Task 5 棘轮口径 — ret N 是栈槽数≠参数个数 ⇒ 真实二进制大量 B 级，棘轮不得按"必须 A 才通过"，须接受 B/C 带证据 — 若错：Task 5 首日死锁
Ruling: _vtable_attack_cases_20260925/ 用例源入库 — verify_fixtures.py 依赖它们（缺目录报错退出）⇒ 必须跟踪入库 — 若错：Task 3 金样本不可复现
Task 3: review package generated (review-53bc72b2f..fd2305f05.diff, 146KB); reviewer dispatched
Task 2: fix round 2/5 dispatched (PE-COFF dir32 reloc crash — Critical, 需扩 _RELOC_LINE + _att_operand 兜底)

## Task 2 R=2 完成

提交：dc209fcec · 测试：38 passed（34+4 新）· 红相验证：34 pass/4 fail → 38 pass
修复：A 治本（_RELOC_LINE 加 dir32|disp32|off32|secrel32）+ B 兜底（$ 非数字回落 other）
真机证据：MSVC6 SP0 /Od + objdump -dr pe-i386 真清单 HEAD 崩 → FIX parsed=37/skipped=19/dropped=0

Ruling: 修复者多改 tests/test_vtable_sig_infer.py（Task 3 文件）— 接受：两条 §15 测试断言 Task 2 抛 ValueError，不翻转即固化已修缺陷 — 若错：Task 3 修复轮需重新对齐这两条
Ruling: Task 3 _PE_RELOC_LINE ⊆ Task 2 _RELOC_LINE ⇒ FEATURE_PARSER_ERROR 不可达 — 保留不删（防御未来形态），记 deferred-minor — 若错：死代码占位
Ruling: Task 3 B 案只护 $（memory head/_parse_mem_expr 符号位移仍崩）— 简报限定 $ 范围，obs 无实测形态，记 deferred-minor 待真机复现再修

## Task 3 评审结果（两裁定 ❌）

Critical C1：deref 分支逃逸 cc_provisional ⇒ grade A 误判（真机 /O2 字节实证：?wr2 与 ?g 逐字节相同）
Important I2：Ruling 6 sret 判据缺连续性（只查 max(covered)>=8）
Important I3：partially_parsed 只加 note 不降级（20/28 行被丢仍 grade A）
Important I4：一地址多候选只在同体时降级（不同体仍 A）
Important I5：iter_candidates（Task 5 遍历面）0 测试引用；CLI 0 测试
Important I6：报告 §1 键格式被证伪（3398 methods 键中 32 个小写）⇒ Task 5 必须键归一
Important I7：金样本可复现性依赖未入库目录（已裁定须入库，待执行）
Minor M8-M12：README 算术错/红相不可验证/--struct 坏/CLI 拒写前缀误拒/死分支

Ruling: Task 3 修复轮 R=1 范围 = C1（必修）+ I3/I4（各一行降级）+ I2（连续性判据+用例）+ I5（补 iter_candidates/CLI 测试）— I6 记入 Task 5 分发要求，I7 控制器执行 git add，M8-M12 延期
Controller: 三个探针目录入库 (commit d0e8fa3a9) — abi_probe 10 + advprobe 9 + attack_cases 20 files
Task 2: R=2 scoped re-review dispatched (review-53bc72b2f..dc209fcec.diff)
Task 3: fix round 1/5 dispatched (C1 deref cc_provisional + I2 sret 连续性 + I3 partially_parsed 降级 + I4 多候选 cap + I5 iter_candidates/CLI 测试)
Task 4: dispatched in parallel with Task 3 fix
Ruling: 并行分发 Task 4 与 Task 3 修复 — 文件可证不相交（layout_assert_gen.py vs vtable_sig_infer.py）+ 无共享接口（grep 确认 Task 4 未引用 Task 2/3 产物）+ 无 IDB 争用 — 若错：git commit 竞态（两者都只 add 自己文件，可控）
Task 2: R=2 re-review ADDRESSED (1/1 closed, 0 new breakage)
Task 2: complete (commits 40dacd759..dc209fcec, 2 fix rounds, review clean)
  - deferred-minor: _RELOC_LINE 名字白名单（未收录 howto 名如 dir32nb/addr32 仍静默退化）
  - deferred-minor: sym(%reg) 形态与 _parse_mem_expr 非数字位移仍抛（R=3 候选，objdump 一般不打印）
  - deferred-minor: IDA 前缀+重定位混合形态不识别（无真实工具产出该形态）
  - deferred-minor: Task 3 FEATURE_PARSER_ERROR 分支零覆盖（保留为冗余纵深防御）
  - deferred-minor: off32 无本机真机发射证据（C 级）
  - deferred-minor: 复审判据工件范围（FIX_BASE 应为 fd2305f05 而非 53bc72b2f）

Ruling: 复审包 FIX_BASE 选择 — Task 2 R=2 的纯净增量应为 fd2305f05..dc209fcec（Task 3 提交在 R=1 复审基准之后）；本次给错范围但评审者自行纠正并完成分析 — 后续跨任务提交后复审须重算 FIX_BASE

## Task 3 修复轮 R=1 完成

提交：d06ede038 · 测试：66 passed（58+8）· 红相：60 passed/6 failed（C1×3+I2+I3+I4）
闭合：C1（deref 分支 cc_provisional+B + convention_from_symbol）/ I2（sret 连续性）/ I3（partially_parsed 降级）/ I4（多候选 cap）/ I5（iter_candidates+CLI 测试）

Controller: 探针源入库（deref_form/rw5/rw6.cpp）—— C1 证据字节实测复现 ✓

Ruling: 顾虑1（/O2 真 sret 被 mov %eax,%edi 截断 store_through）— B 级不误给 A ⇒ 记 deferred-minor，不阻塞本修复轮 — 若错：arity 多 1 的 B 级候选被 Task 5 当确定签名（风险低，B 级带证据）
Ruling: 顾虑3（mangling 作元数据旁证）— 接受：仅在"字节不可判"的 deref 形态使用 + 清栈自洽校验 + cc_from_mangling 留痕 — 若错：Task 5 可单列复核
Ruling: 顾虑4（A 级占比下降）— Task 5 棘轮须接受 B/C 带证据（已记 Task 5 分发要求）

## 测试污染诊断（Task 3 测试 66→65 异常）

现象：test_vtable_sig_infer.py 从 66 passed 变 65 passed/1 failed
根因：**测试污染**——`data/annotations/__r1_cli_must_never_write.json` 残留（早期 CLI 版本或部分状态运行时创建）
验证：清理后 66 passed ✓；直接测 CLI 拒写生效（"拒绝写入真相源目录" + 文件未创建）✓
结论：**非 bug，是测试脆弱性**——测试未在断言前清理 forbidden 路径

Ruling: 测试脆弱性修复捆绑进 Task 3 R=2 — 断言前先清理 forbidden 路径（测试卫生）— 若错：污染再现导致假失败

## Task 3 修复轮 R=1 复审结果

C1/I2/I3/I4/I5 **全部 ADDRESSED**（独立复现验证）
独立证据：309 真实函数（44 单元 × /Od+/O2）old-vs-new 0 条 grade 放宽；真机 deref_form 17 字节相同；I5 诚实性验证（pre-fix 树 60/6，RED 恰为 6 条行为测试）

### 新增破环候选（需裁定）
sret_ambiguous 对"多基址+>8B+不连续"不可达 ⇒ 安全 B 变 A（无痕迹）
- 同输入：old=B+{sret_ambiguous,hidden_param_suspicion}；new=A+无痕迹
- 可达性未证成（真实 /Od 结构复制连续；/O2 store_through 空落 B；309 函数 0 grade 放宽）
- 评审者已验证 1 行修法：`elif len(bases) > 1 and max(covered) >= 8: sret_ambiguous = True`

Ruling: 升级为必修（Task 3 R=2）— "无字节级证据不得给 A"是 A 级契约核心，Task 5 棘轮按 grade 消费；1 行修法已验证且 66 passed 不回归 — 若错：一次多余的修复轮（代价小）
Ruling: 捆绑 3 项收尾（测试污染清理 / 新夹具接入 verify_fixtures / 3 处 8b e5 手抄修正）— 同为 Task 3 文件，批量修复 — 若错：夹具不完整

## Task 4 完成（DONE_WITH_CONCERNS）

提交：daeb68fcc（11 文件）· 测试：46 passed / 8 变异体全杀 / 前序 35+38+66 无回退
交付：layout_assert_gen.py(933行) + 探针目录（shape/off/dup2.cpp + verify_generated_asserts.py + check_shape_against_binary.py + census + 样张）
真机编译器裁判 ALL CHECKS PASSED：正相 31 生效断言 0 错误；4 类负相全被 C2118；虚基成员 C2057

### 三条硬结论（真机证据）
1. PMF 判据必须走**传递闭包**：`DERofMI2 : MI2`（单直接基但基类是多继承）实测 8 而非 4 —— 真实数据有 `CCBRoleState : SceneObj` 这类实例
2. offsetof 跳过集合 = 虚基 ∪ 其传递闭包
3. 可疑常量默认"留痕不生效"（trusted/same-source/suspect 三态）

### 真实数据（881 类/10918 断言）
生效 176（全是形状断言）· [SAME-SOURCE] 68 · [SUSPECT] 10674 · 跳过 2

### 顾虑裁定
Ruling: 顾虑1（UIEmote baseclass2 内嵌建模 vs 二进制真 MI）— 接受生成器 [SUSPECT] 降级（正确保守）；注解不一致记 deferred（属 codegen/注解层，非 Task 4 范围）— 已独立验证：base_class 双基 + known_members baseclass2@0x44 并存
Ruling: 顾虑2（全仓 0 虚基标记）— 已验证属实；当前若有虚基按 MI 处理会假失败 ⇒ Task 8 必须用 vbtable 反查回填 — 若错：虚基类形状断言假失败
Ruling: 顾虑3（--evidence 生产者缺失）— 接受；Task 8 建"IDA 二进制→证据 JSON"生产者 — 若错：size/offset 断言只能留痕（当前状态）
Ruling: 顾虑4（同名 typedef 非 C2086）— 简报口径修正（实测 C2369/C2371/C2372/C2040）— 若错：命名唯一性强制过度
Ruling: 顾虑5（全量头 2.3MB 不入库）— 接受只入 census + 样张 — 若错：需重生成
Task 6: dispatched (vtable_verify — 编译产物对比，最终裁判)
Task 7: dispatched (虚调用转换 — stage3 扩展)

Ruling: 并行分发 Task 6/7 与 Task 3 R=2 — 文件可证不相交（vtable_verify.py 新 / stage3_cleanup.py vs vtable_sig_infer.py）+ 依赖已满足（Task 1/2 完成）+ 防 IDB 争用约束（禁跑 pipeline loop/apply/export，只跑自身单测）— 若错：git commit 竞态（各自只 add 自己文件）

## Task 3 修复轮 R=2 完成

提交：3e841f78c（3 files, +130/−15）· 测试：68 passed（66+2）· 夹具 39→43→44（控制器补 rw7）
闭合：sret 安全网恢复（1 行 elif）/ 测试卫生（清理移到 CLI 调用前）/ 夹具自证 / 3 处手抄字节修正

Controller: rw7.cpp 入库 + verify_fixtures 接入（commit）—— 夹具 44 条/不一致 0 ✓

Ruling: 顾虑b（新 elif 依赖 bases/covered 同源不变量，未加 covered 守卫）— 接受（当前不变量成立），记 deferred-minor 供日后重构复查 — 若错：covered 空时 max() 抛异常
Ruling: 顾虑c（修复项4 对 verify_fixtures 非惰性）— 接受：不修则新夹具接入即 3 条 MISMATCH，两项耦合是正确发现 — 若错：无
Ruling: Task 5 必须读 features 区分 sret_ambiguous vs hidden_param_suspicion — 不能只看 grade — 记入 Task 5 分发要求
Ruling: Task 5 棘轮须接受 B/C 带证据（A 级占比因 C1/I3/I4 降级进一步下降）— 记入 Task 5 分发要求
Task 5: dispatched (vtable_decl_check — 声明校验棘轮制)
Task 3: R=2 scoped re-review dispatched

Ruling: 启动 Task 5 而非等待 Task 3 R=2/Task 4 CR — 依赖在功能上就绪（Task 1 完成 + Task 3 签名产物 68 测试 + Task 4 布局断言 46 测试+编译器验证）+ 文件不相交（vtable_decl_check.py 新建）+ 待完成的两个 CR 是确认性评审（审已提交已测试代码）— 若错：CR 发现问题时 Task 5 需微调消费口径（代价小、可见）
Task 3: R=2 re-review ADDRESSED (4/4 closed, 0 new breakage)
Task 3: complete (commits fd2305f05..7b3c21bd4, 2 fix rounds, both reviews clean)
  - deferred-minor: DTOR_GV 手抄夹具未接入 verify_fixtures（fd2305f05 遗留）
  - deferred-minor: C1 两真值逐字节相同在测试中同义反复（1492 行 body_key(X)==body_key(X)）；?g@C 未单独上 FIXTURES ⇒ ?g 字节一致性仅有探针源/报告佐证
  - deferred-minor: FIXTURES 把 C1_R2_MULTI_BASE_GAP 插在 RW1 组中间（仅美观）
  - deferred-minor: task-3-report.md R=2 段落滞后最终 HEAD（写 43 条/rw7 未接入，实际 44 条已接入）
  - deferred-minor: 新 elif 的 max(covered) 未加 covered 守卫（当前构造保证非空）
  - deferred-minor: 卫生 helper SIGKILL 场景仍可能留文件（已不再致假失败）

独立验证高点：pre-fix 精确复原（特征集与 pre-R1 完全相同）；语料级 63 函数仅 1 条变化（rw7 目标本身）；绑定检验（pre-fix 恰好 1 条 RED）

## Task 4 评审结果（两裁定 ❌）

### Critical（3）
C-1 间接虚基漏跳 offsetof：virtual_base_region 只遍历**直接**虚基（layout_gen.py:361）；实测 `VB2:virtual V1; IVB:VB2` ⇒ offsetof(IVB,vv) C2057+C2466 而生成器返回可断言
C-2 `--virtual-bases` 与 base_names **求交** ⇒ 间接虚基静默丢弃（Task 8 回填入口失效，零 warning）
C-3 PMF 规则不完备 ⇒ **真实发射头 1 条默认生效断言假杀**：`RoleCameraCtrl : PalScriptWaitObj`（PalScriptWaitObj 发射头 0 virtual）真值 8，生成器给 4 ⇒ C2118

### Important（3）
I-1 6 个 CEffTrack* 的 base_class 重复间接基 ⇒ C2584（**已验证：6 类均无 .cpp ⇒ 潜伏未阻断**）
I-2 "size/offset 零判别力"推理过宽 ⇒ 实际覆盖仅 176/10918 = 1.6%
I-3 产物未接入 codegen include 链 ⇒ 今日无断言生效（Task 8 接线）

### 控制器验证
- C-3 可达性：RoleCameraCtrl.cpp **存在**（参与编译），但 _layout_asserts.h 未接线 ⇒ 潜伏
- I-1 可达性：6 个 CEffTrack* **无 .cpp** ⇒ 未编译 ⇒ 潜伏

Ruling: C-1/C-2/C-3 立为 Task 4 R=1 必修 — 均为"接通前必修"（Task 8 接线时引爆），且 C-2 使 Task 8 唯一回填入口静默失效 — 若错：Task 8 接线即硬编译中断
Ruling: C-3 修法采"按 vtables（非 methods）判多态 + 无发射头/外部类一律 SUSPECT" — 评审者候选规则在 176 真实断言上 0 反例，但外部类过判（gbTexture 实测 4）⇒ 必须叠加 SUSPECT 兜底 — 若错：外部类形状断言误报
Ruling: I-2 捆绑（增设 consistency-only trust 档）— 低成本恢复覆盖 — 若错：档位语义需文档
Ruling: I-1 转注解修复（6 类去重间接基）— 非 Task 4 引入 + 当前潜伏 — 若错：接通后 C2584
Ruling: I-3 归 Task 8（接线职责）— 本任务只需文档化契约

## Task 6 完成（DONE_WITH_CONCERNS）

提交：0c6fde7eb（vtable_verify.py 1484 行 + test_vtable_verify.py 1012 行）· 测试：39 passed/2 skipped（VTV_LIVE=1: 41 passed）
交付：name_key 符号归约 · obj_vtables/obj_vbtables · decode_adjustor_chain · normalize_obj_slots/normalize_bin_slots · compare_tables/compare_vbtable（7 kind）· ProbeSpec/force_emit · CLI
真机证据：c2.obj B-1 复合槽 ⇒ ('D::~D','composite','dynamic',16)；vt3 静态 thunk ⇒ (D3::ff,adjustor_static,8)；PAL3 0x56AB28[2] ⇒ (gbLightObj::GetCGEntry,8)；189 张表与 vtable_compare 0 分歧

### 🔴 顾虑1（跨任务 Critical 架构发现）—— 控制器已独立验证
**/GR ⇒ COL ⇒ vtable 维度结构性不匹配**
- 实测：带 /GR ⇒ `??_7B@@6B@` value=4（COL 在 value-4）+ 2 个 R4 符号；不带 /GR ⇒ value=0 + 0 符号
- PAL3.exe：仅 6 条 .?AV 串**全是 CRT/STL**（_Exception/exception/logic_error/length_error/out_of_range/type_info）⇒ **游戏类无 RTTI**
- 管线带 /GR：MSVCSettings.cmake:89 + compare.py:69/81 + cli.py:690
- ⇒ 原二进制 = 无 RTTI 布局；我们带 /GR ⇒ 每张表多 4 字节 + 逐槽位移 ⇒ **vtable byte-match 结构性不可能**

Ruling: /GR 是 Critical 架构问题 — 用 /GR 编译的 obj 与无 RTTI 二进制在 vtable 维度永久不匹配；修法是移除管线 /GR（匹配二进制布局）— 若错：需保留 /GR 则 vtable 维度只能做"归一化对比"而非 byte-match
Ruling: 移除 /GR 的影响面 — 属管线级改动（cmake/compare.py/cli.py），~~L1 比对 .text 不受直接影响~~；须以 spike 验证（编译探针对比二进制 .rdata）后再落地 — 归 Task 8 或专门 spike
  ❌ **2026-09-25 全分支最终评审更正（本条前半句是错的）**：`/GR` **就在生产 L1 的 flags 串里**
  （`pipeline/cli.py:690` = `/nologo /TP /c /W3 /O2 … /GR /MD /Gd` = `data/status/s4_baseline.json.flags`）
  ⇒ 移除 `/GR` **会改变生产 L1 编译标志**，`.text` 字节比对**必然**受影响、**L1 基线须重测**，
  **不得**假定"L1 口径不变 / 不受直接影响"。原表述把 `/GR` 误当成只属 `.rdata` 维度的开关，
  根源是同一轮里把 `compare_pal3.PROBE_FLAGS`（probe 默认口径）误当成生产 L1 口径
  （见下方"全分支最终评审结果"的 ★Critical）。正确表述见 T1 工单与 task-8-report §2。
Ruling: 顾虑2（二进制表长启发式）— 接受 confidence/broken_at 留痕，low 须人工核
Ruling: 顾虑3（MI 继承槽名归属差异）— 接受故意不自动判等（否则放过错误基类函数）
Ruling: 顾虑4（vbtable 需二进制 VA）— Task 8 证据生产者补
Ruling: 顾虑5（force_emit 需 ctor_declared）— 接受消费方提供

## Task 7 完成（DONE_WITH_CONCERNS）

提交：7ee6041fb（stage3_cleanup.py +1101/−53 + test_vtable_call_transform.py）· 测试：27 passed（红相 1/20 failed）
交付：三形态解码器（inline/局部 vftable 变量/裸 vptr）+ 名称解析链 + 头文件一致性护栏 + 失败契约
真机证据：3598 decomp 函数差分 identical 3540/changed 58/转换 113/新增行 0；5 个转换名全命中 virtual 声明
★ 实测真缺陷挡下：UIWnd 槽3 IDB 名 Destroy 但该类 Destroy 声明在 0x0043BBB0 且**非 virtual** ⇒ 直接发射会绑到非虚函数 ⇒ 新增一致性护栏

Ruling: 顾虑a（契约读法）— 接受实现者读法（legacy stub 逐字不变 + 新形态失败原文保留）— 与规格"保留既有 stub 语义 + 记账"一致；另一读法（新形态也合成 stub）产生 ≈460 新 stub，需完整 pipeline 量测，受并发约束未盲改 — 归 Task 8 量测
Ruling: 顾虑b（护栏不扫 decomp）— 接受，当前代价 0（113 处名全命中三源）— 若错：decomp-only 名记账不转换
Ruling: 顾虑c（无端到端字节验证）— 归 Task 8
Ruling: 顾虑d（台账未入库）— 控制器已补提交 ⚠️**（该「已补提交」已被下文 `:401` 的「更正 M5」撤销（评审引用编号 `:381` 为本轮新增表注 M-1 之前的位置）；勿线性引用本行）**
Ruling: 顾虑e（COM/函数指针成员不处理不记账）— 接受（避免误判）
Controller: data/status/vtable_transform_failures.md 入库 ⚠️**（前提同上：言行状态已被 `:401` 更正为「运行时产物，Task 8 首次 pipeline 运行后随提交入库」；本行不是"已入库"的证据）**

## Task 5 完成（DONE_WITH_CONCERNS）

提交：50ecae6f4（vtable_decl_check.py 1408 行 + test_vtable_decl_check.py 1090 行/81 测）
测试：81 passed / 0 failed；前序 35/38/68 无回退
真实数据：78 类/841 槽（与 vtable_baseline total_slots=841 相符）；flat slot_health 0.588585；全对 45 类/全错 10 类
真实头变异 3 条全部报警且棘轮阻塞

### 关键归因线索（Task 8 用）
- **CEffectSystem Reset@0x4C6260 被发射器排在槽 1，二进制在最后（8 处错位）** ⇒ 发射器槽序发射有误（与 Task 1 槽序规则对照）
- CGameData 同时有 `virtual ~CGameData(){}` 与 `virtual void _scalar_dtor()` ⇒ **8 声明 vs 7 槽**（槽数项如实报警）

Ruling: 顾虑1（chain 模型不可用，0.306）— 根因已定位（发射器补位槽名 slot_N 按本表下标 ⇒ 基类同名槽不同名 ⇒ match_key 认不出继承）⇒ 修发射器补位命名属 Task 6/发射器范围，记 deferred — 若错：MI 逐视图校验不可用（当前 flat 模型仍工作）
Ruling: 顾虑2（注解 vtables[] 不完备+多视图语义混乱）— 这正是 v3 规格已知的完备性缺口（对抗评审 A1）；未匹配表记 view_unmatched+0 分（保守）— 接受
Ruling: 顾虑6（CEffectSystem 8 处槽序错位 + CGameData 8vs7）— 立为 Task 8 归因项（真实差异，非本任务 bug）— 若错：遗漏真实布局问题
Ruling: 顾虑3/4/5（--write-baseline 显式/无管线集成/sig_health None）— 接受，Task 8 接线 + 取当日基线
Ruling: 顾虑7（无硬门禁）— 接受（专门测试钉死不降即放行，防 v2 不等号反向复发）

## Task 6 评审结果（两裁定 ❌）

C1（Critical）v3 规格"槽序（符号名→VA 归约序列）"未在交付路径实现：
- `va_of` 只作参数（708/770/815-820），main() 对比模式（1338-1339）**不传** ⇒ 两侧 va 恒 None ⇒ identity 退化为名字文本比较
- 真机量化（189 表/639 槽）：406 槽 bin 键带参数表（`Cls::m(void)`）obj 侧 mangled 归约永不带 ⇒ 必然 slot_key；146 槽退化成 0x<addr> ⇒ **≥552/639 = 86.4% 槽在表完全正确时也误报**
- 同源缺陷：839 行 resolve(key) 名字反查而丢弃真实已知目标 VA（th.target_va/槽 VA）
- 实例：报告引为证据的 0x56AB28 表 3/3 槽误报

Important：I1 无任何测试走 CLI 对比路径/真机名字形态（病因）；I2 dummy_ctor 无 LIVE 覆盖（行为已验证正确）；I3 报告 §2.1 输出删减

Ruling: Task 6 C1 立为修复轮 R=1 — "最终裁判在真数据上 86.4% 误报"使其事实上不可用，Task 8 会照 §1 API 直接消费 — 修法：main 由 idx 造 name→VA（剥参数表归一）传 obj 侧 + bin 侧直接用真实目标 VA + 补真机名字格式+CLI 对比路径回归测试

## Task 7 评审结果（两裁定 ✅）

独立复现：27/27 测试 · 前序 10 文件全绿 · 全语料差分逐数字复现（3540 identical/58 changed/113 转换/0 异常）· 台账 464 行原因与形态分布逐格一致 · 跨进程幂等 md5 三次全同 · UIWnd 槽3 护栏真实数据独立证实

### Important（建议 Task 8 前修）
I-1 **护栏旁路**：stage3_cleanup.py:855-866，`slot_addr=''` 时 `if decl_addrs:` 与 `elif slot_addr:` **双双跳过** ⇒ 直接 return name
  - 实测暴露 10 个 (类,槽)：CCBPanelSlot 槽3-6、PalScriptMgr 槽0-5
  - 直接证据：`_resolve_vtbl_name_chain('PalScriptMgr', 12)` → `('Destroy_3', None)`（头文件与注解均无此名）
  - 且 PalScriptMgr IDB vtbl_0056ABB8 槽名与二进制槽序**已实证错位** ⇒ IDB 回落会是字节错误的虚调用
  - 当前语料 0 触发（907 次解析全量计量）⇒ 触发即 Critical
  - 最小修法：slot_addr 缺失即 `return None,'no_slot_addr'` + 1 测试
I-2 **新增注解直读**：`_load_vtbl_index()` :709-760 直接 os.listdir+json.load `data/annotations/structs/*.json`，绕过 `pipeline/gen/annotation_view.py`（CLAUDE.md 明文要求）⇒ 用 `annotation_view.iter_structs()/load_struct()/structs_dir()` 零风险替换

### Minor
M1 `_VTBL_VPTR_READ` 的 `^\*+` 过宽（建议收紧为单 `*`）
M2 报告 §5.7"不记账"表述不准（`**(T**)X+N` 子族被解码并记账）
M3 台账键不含调用文本 ⇒ 同函数内多站点只记 1 行（Task 8 当工单会低估）
M4 §4.2"ADDED 行 0"措辞（实为 113 行全为转换行）
M5 台账不在仓库 ⇒ 本为运行时产物，Task 8 首次 pipeline 运行后随提交入库
M6 全语料 `__vftable`=0 ⇒ legacy 分支实际不触发（"3540 逐字节相同"未覆盖 legacy）
M7 测试覆盖缺口（no_class_hint/non_class_hint 240 行无单测、`V=OBJ->__vftable` 无单测、`const Cls*` 归一无单测、slot_addr 缺失路径无测试）
M8 端到端字节裁决归 Task 8（替代验证：所有可解析转换的实参个数与声明一致）

Ruling: Task 7 R=1 修复 I-1（护栏旁路，一行门+一测试）+ I-2（annotation_view 替换）— I-1 触发即 Critical（PalScriptMgr 会发射凭空名/字节错误虚调用）— 若错：Task 8 接线后 C2039 或字节错误
Ruling: 更正 M5 — 台账为运行时产物，非控制器提交遗漏；Task 8 首次 pipeline 运行后入库 — 撤销先前"已补提交"表述
Ruling: M1-M4/M6-M8 记 deferred-minor

## Task 5 评审结果（两裁定 ✅）

独立复现：81/81 测试 · 前序 35/38/68 全绿 · flat 真实数据（78 类/92 view/841 槽/0.588585/全对 45/全错 10）逐字相符 · chain 0.305589 · 生成头 744 个/948 行 virtual/未解析 0 · Ruling 3 普查（3398 键/32 小写）吻合 · 棘轮三态真实树复现 · CEffectSystem 8 处 mismatch 非构造 · 无硬门禁
Ruling 1-5 逐条独立复现（R2 的 sret_ambiguous vs hidden_param_suspicion 豁免集可区分；R4 'fn' 直传 Task1 确被判合成单槽组）

### Important（Task 8 接线前必修）
Q1 **证据缩水被奖励并锁进基线**：棘轮只比**比值**，`build_baseline` 的 slots/count_denom/count_ok/overall.slots_total **不参与对比**
  - 删掉一个**未声明**槽 ⇒ slot_health 0.5→1.0 ⇒ 判 improved 并**回写基线**
  - 同时删声明与其槽 ⇒ 3 槽→1 槽 ⇒ 三分量全 same ⇒ 放行
  - **最重后果**：基线被改写 1.0 后，**把缺失证据补回来（注解完备性修复）反而 BLOCKED** ⇒ 拦住正确修复（CLAUDE.md 假失败模式）
  - 修法：每类 slots/count_denom（或 count_ok）作为第 4 类单调分量纳入棘轮（"验证面不得缩小"）
Q2 **静默关闸**：`--write-baseline` 无 `--baseline` ⇒ exit 0、不落盘、无告警 ⇒ 无基线 ⇒ decision None ⇒ **一切恒 exit 0**（门禁永久静默关闭）⇒ Task 8 漏写 `--baseline` 会得到"永远绿"假门禁
  - 修法：报错 rc=2 或隐式用默认路径 + CLI 测试
Q3 **签名分量单向 unmeasured**：base 有值 ∧ 当前 None ⇒ 应判 down/阻塞（证据源丢失=倒退）
Q4 **真实数据锚点把"当前缺陷状态"钉死**：`total==841` 硬编码 / CUtil 恰 7 条 / 要求至少 1 个 health==0 / 要求 CEffectSystem 错位必须存在 ⇒ Task 8 修好即**为正确改动报红**
  - 修法：锚点改读 vtable_baseline.json 或断言"不劣化"；缺陷存在性用 xfail/条件断言

### Minor
Q5 写入路径未保护（FileNotFoundError ⇒ exit 1 与"阻塞"相撞，应 rc=2）· Q6 purecall 适配无直接断言 · Q7 Ruling 5 静态守卫是字面串匹配 · Q8 无基线时 report_to_dict 缺 ratchet 键 · Q9 TDD 红态不可从 git 复现（间接佐证充分，可接受）

Ruling: Task 5 R=1 修 Q1/Q2/Q3/Q4 — 四项均为门禁语义洞且 Task 8 接线前必修（Q1 会拦住正确修复、Q2 会造成永久假绿、Q4 会为正确改动报红）— 若错：门禁失去判别力或误拦
Ruling: Q5/Q6 成本低则捆绑；Q7-Q9 记 deferred-minor

## Task 7 修复轮 R=1 完成

提交：69714f977（stage3_cleanup.py +43/−13 + test_vtable_call_transform.py +132）· 测试：35 passed（27→35）
I-1 fail-closed：`if not slot_addr: return None,'no_slot_addr'`；红相端到端跑出凭空名 `this->Destroy(1);`；全语料旁路触发 0
I-2 收敛 annotation_view：等价性实测 identical: True（五张表逐字段，classes=80/idb_vtbls=92/slot_addrs=80）
M1 `^\*+`→`^\*`：语料命中 30→0，**全语料输出 changed=0/added=0/removed=0**（113 转换全保留）
M7 补 no_class_hint/non_class_hint 单测

Ruling: 顾虑1（stage3:173-191 legacy 兜底仍直读 structs/<Cls>.json）— 属 CLAUDE.md 已知 3 处直读之一（行号漂移），不在本任务范围 ⇒ 记 deferred，独立工单 — 若错：直读违规持续
Ruling: 顾虑2（no_slot_addr 使 10 槽转记账）— 注解工单方向改为"补 slots[i].addr" — 接受
Ruling: 顾虑3（无端到端字节验证）— 归 Task 8

## Task 4 修复轮 R=1 完成

提交：1ce864e2f（10 文件）· 测试：73 passed（46→73，+27）· 6 变异体全灭 · R=0 编译器裁判仍 PASSED
C-1 修：virtual_base_region 遍历 {layout}∪闭包；探针 ivb.cpp:22 复现 C2057+C2466
C-2 修：覆盖名一律加入 bases + 未知名 WARN + 降级；实测 pmf 4→12、region []→{V1}
C-3 修：①载体判据改用注解 vtables（新 ClassLayout.has_vtables；证据 emit_headers.py:2460）②规则"最基层载体有直接基⇒8"（探针 pmf_intro.cpp /FAs 确证）③兜底 gb*/名单外⇒SUSPECT ④**新增端到端裁判 verify_emitted_asserts.py**
  - 实测：**140 编译 = 132 PASS / 0 假杀** / 8 头自身编不过（= 评审独立复算同一集合）
  - 变体检验：退回 R=0 ⇒ 裁判立刻抓到 `FALSE-KILL RoleCameraCtrl` + C2118（与评审"1 假杀"对上）
I-2：consistency-only 独立 trust 档；真实数据该档 8846 条（默认 0）

Ruling: 顾虑1（I-2 档是漂移探测器非可常开闸：抽样 1841 条 ⇒ 64 假杀+71 C2039）— Task 8 必须**按类试运行**（--only），禁一次性全开 — 若错：include _layout_asserts.h 的 TU 直接编译失败
Ruling: 顾虑2（生效断言 176→140，减少 36 = 23 gb* + 13 闭包含 gb*）— 属"规则不可证⇒降级"的保险，非修 bug；Task 8 纳入 spec 头 virtual 可恢复 — 接受
Ruling: 顾虑3（8 个发射头自身编不过：6 CEffTrack*=I-1 已转注解修复；2 个 CCBParabolaWindow C2555 + PlayerAtt C2061）— 后 2 个另立任务 — 记 deferred
Task 7: R=1 re-review ADDRESSED (I-1/I-2/M1/M7 全部, 0 新增破环)
Task 7: complete (commits 7ee6041fb..69714f977, 1 fix round, both reviews clean)

独立验证高点：旁路面枚举恰好 10 个 (类,槽) 与发现项逐一吻合；非 I-1 路径 old/new 分歧 0（无过度拒绝）；AST 级检查（非子串 grep）确认 I-2；全语料 A/B 3598 文件 identical=3598/changed=0/errors=0
根因精确化：不是"slots[i] 有字段但为空"，而是**注解 vtables[0].slots[] 比 IDB vtbl_* 成员短/空**（CCBPanelSlot ann=3 vs IDB=7；PalScriptMgr ann=**0** vs IDB=6）⇒ fail-closed 正打在此危险路径

延期 minor：
1. 台账覆盖面收窄（old 464→new 439，only_old=25/only_new=0，全为 `**(_DWORD**)X+N` 双解引用族）⇒ 旧误归类记账、新零覆盖（0 输出变化）⇒ Task 8 若在其中发现真虚派发需显式原因
2. 报告 M1 台账数字不可复现（报告 197/187/12/2 vs 实测 464/439/25/0）⇒ 实质结论独立确认，仅数字需更正
3. 报告 R=1 顾虑 2 措辞会指偏工单：那 10 个槽在注解 slots[] 里**根本不存在**（PalScriptMgr slots 为空）⇒ 工单应为"补 slots[3..6]/[0..5] 条目（含 addr）"
4. stage3_cleanup.py:173-191 legacy 兜底仍直读（blame e848e431d 2026-06-04，非本轮）⇒ CLAUDE.md 3 处直读之一，独立工单
5. pipeline/gen/test_pipeline.py 6 条失败经沙箱双实现复跑证实**既存**（与 Task 7 R=0/R=1 无关）

## Task 6 修复轮 R=1 完成

提交：7a5b24ad7（vtable_verify.py +566/−22）· 测试：52 passed（39→52，+13）· VTV_LIVE=1: 55 passed
修法三处：①main() 造 namemap=name_to_va_index(idx,image) 传 va_of ②normalize_bin_slots 的 va 直接取 th.target_va/槽 VA，删名字反查（删 va_of 入参=契约变更）③新增 strip_param_list+NormSlot.name_id，两侧都有 VA 比 VA 否则比 name_id（绝不混比）

真机数字：
- 评审引例 0x56AB28：修复前 3 槽全报 → 修复后 `✅ 逐槽一致 identity=va EXIT=0`
- 真机全库 187 表/639 槽：修复前 ≥552 必误报 → **469 槽走 VA、0 VA 冲突**（修复前 8 处全 adjustor thunk，由 thunk 名重定向消掉；真机 103 重定向/53 重载歧义剔除）
- 真机 10 对偏差**逐一相同**（只去假报无假通过）；AStarPathFinder 仍报 4 处 EXIT=1
- CLI 对比路径此前**零覆盖**（C1 漏过病因）已补

Ruling: 残项 146 槽（22.9%，import stub `ff 25 <IAT>` 79 + 未命名函数 67）— 两侧判据都不可用（无名字且无可用 VA），仍保守报 slot_key + notes 写明；评审要求的"0 VA 冲突"已达成 ⇒ 接受，归零需补名字源（idx 覆盖/PE import 表解析）属新增特性 ⇒ 记 deferred，需显式授权才扩范围
Ruling: 契约变更（normalize_bin_slots 删 va_of 入参）— 仓内无其他调用方；Task 8 需知会 — 记入 Task 8 分发要求
Ruling: COMDAT 折叠别名假报边界 — 真机 0 冲突，已留档 — 接受
Task 4: R=1 re-review ADDRESSED (C-1/C-2/C-3/I-2 全部, 0 新增破环)
Task 4: complete (commits daeb68fcc..1ce864e2f, 1 fix round, both reviews clean)

独立验证高点：
- 端到端裁判 verify_emitted_asserts.py = 140 编译：132 PASS / 0 false_kill / 8 header_error；--self-test OK
- C-3 独立编译：`sizeof(PMF)==8` 干净、`==4` ⇒ C2118（真值 8）；生成器现给 8
- 新规则对 pmf_intro.cpp 全部 12 个编译器自算常量 0 失配 + 4 个未入矩阵边例全对
- C-1 独立复编 ivb.cpp：间接虚基行 C2057+C2466；生成器 region={V1}、member_offset_assertable=False
- C-2 合成 D：pmf 4→12 + region={V1} + warning；R=0 仿真复现缺陷
- 默认口径 active 176→140（36 降级）经独立检验为**有据的保守降级**（gbTexture 实测真值 4 而规则给 8 ⇒ 真机 C2118 确认假杀）

延期 minor：
1. 探针行号陈旧（ivb.cpp 实际 28/31/32/36，注释/README/docstring/commit 写 22/25/26/30；错误码与语义正确）
2. 报告 §R=1.4 的 8986/8846/1932 需 `--declared-classes <768 类>`，展示命令漏该 flag
3. 8 个发射头自身编不过（6×CEffTrack*=I-1、CCBParabolaWindow C2555、PlayerAtt C2061）
4. gb* 前缀门默认损失 6 条今天能过的 gb 断言 + 13 条非 gb（保守保险非错误）

## Task 5 R=1 复审结果（Q1-Q6 全 ADDRESSED + 1 新增过严路径）

独立实测：87/87 测试 · 前序 35/38/68 绿 · 真实数据 e2e 四条不变量全部复现
Q1 复跑：①删未声明槽 ⇒ slot_health 0.5→1.0 但 blocked ✓ ②删声明+槽 3→1 ⇒ blocked（slots 3→1 down）✓
  ③**删 AStarPathFinder 未声明槽后 --write-baseline ⇒ rc=1 且基线 sha256 逐字未变** ✓
  ④**完备性修复（~AStarPathFinder() → virtual ~AStarPathFinder()）⇒ rc=0/improved/基线回写** ✓（假失败前提消除）
Q2 实测 rc=2 + stderr + 无落盘 ✓ · Q3 双向实测 ✓ · Q4 模拟 Task 8 修复后仍 87/0 ✓ · Q5 两处写入 rc=2 ✓ · Q6 purecall 断言 ✓

### 新增过严路径（需裁定）
`count_denom` 单调把"删除任何声明"判 down ⇒ 对"冗余/错误声明的正确清理"过严阻塞
- 实测：删 CGameData.h 重复注入虚析构（无地址）⇒ 工具自己 count_ok False→True、count_health 0.875→1.0，却被 count_denom 8→7 down 判 blocked/updated=None
- 旧实现该改动是 pass 并回写基线 ⇒ **新增过严路径**（Q1 严格只需 slots）

Ruling: 降级为 `_SURFACE_METRICS=(METRIC_SLOTS,)` — slots 才是真正的验证面（注解 vtables 槽数）；count_denom 合法地随声明清理变化；且 slots 单分量已能捕获 Q1 两洞（①改 slot_health ②slots 3→1 down）— 若错：丧失"声明数不得缩小"的一层保护（但该层会拦住正确清理，代价更大）
Ruling: 延期 minor（锚点以注解派生冻结快照为下界 / `else: assert mean > 0.95` 逻辑不成立 / --json 失败先于棘轮判定 / TestRealDataMutation 留 CUtil 绝对锚点）— Task 8 同提交用 vtable_mapper 刷新基线或换 IDB 侧真值 — 记 deferred

## Task 5 修复轮 R=2 完成

提交：f87ea44b7 · 测试：88 passed（87+1）· 一行降级 `_SURFACE_METRICS=(METRIC_SLOTS, METRIC_COUNT_DENOM)` → `(METRIC_SLOTS,)`
TDD 红→绿：改前 86 passed/2 failed（①新测试Q7红 ②Q1-b改强断言红）→ 改后 88/0

Q1 两洞仍封死（实测）：
① 删未声明槽（slots 2→1, slot_health 0.5→1.0）⇒ 仍 blocked ✓
② 删声明+槽 3→1 ⇒ 仍 blocked（**断言 count_denom 不再出现在 d.components** ⇒ 证明封死靠 slots 单分量）✓
③ 删冗余声明 ⇒ **现在 pass/improved + 回写基线** ✓（新测试 + 反向守卫：加回来不得读成 improved）

真实数据 A/B：真 CGameData（count_denom 8/count_ok False）模拟删无地址虚析构 ⇒ R=1模拟 blocked(`count_denom 8→7 down`) vs **R=2实装 improved/passed/updated=YES** ✓
全仓核查：`_SURFACE_METRICS`/`count_denom` 无其他消费者 ⇒ 降级不破坏调用方

Ruling: 顾虑1（失去"声明数不得缩小"保护）— 缓解成立：count_denom 仍是 count_health 的分母，删**被覆盖**声明 ⇒ count_health（仍为比值分量）下降 ⇒ 仍阻塞（反向守卫钉死）— 接受
Ruling: 顾虑3（count_ok 非棘轮分量）— 保持现状（count_ok 单调会让"新发现无地址声明"阻塞合法新证据，风险更高）— 接受

## Task 6 R=1 复审结果（C1 ADDRESSED + 1 新增假通过面）

独立复现：
- 真机量化：误报 **552（86.4%）→ 146（22.8%）**；**469 槽走 VA、0 冲突**（原 8 处 adjustor thunk 冲突消失）
- 引例 0x56AB28：OLD 3/3 slot_key；NEW identity=va、0 偏差（槽2 thunk 正确归约到 jmp 目标 0x423860，非 thunk 本体 0x42C8D0）
- 表级：114/187（61.0%）clean；61 表含 ≥1 无名字残留槽
- **无假通过（真数据）**：8 对真 .obj×真表，偏差列表 old/new **逐条相同（66/66，fewer=0/more=0）**，而 identity_mode 在 7/8 对变化（证明接线在真编译产物上生效，非仅夹具）
- 反向控制：向真 0x56AB28 槽1 注入错误目标仍报 slot_key index1 ✓
- 变异检验：运行时丢弃 va_of ⇒ 2 条新测试双双变红（真守住接线，非同义反复）✓

### 新增破环（需裁定）
歧义名剔除后，24 个真机槽（3.8%）的 name_id 对应 ≥2 个 VA（24/24 候选体各不相同 ⇒ 真重载/调整变体）
- obj 侧 va 退为 None ⇒ 走名字判据，而 `name_key` **抹掉参数编码**（`?DestroyEffBase@RenderTarget2@@UAEXD@Z` 与 `...UAEXXZ` 同为 `RenderTarget2::DestroyEffBase`）
- 真机实证：表 0x56f668 槽2 装 `DestroyEffBase(char)`@0x4C1640；若 .obj 装 `(void)`@0x4C1660 ⇒ `compare_tables` 返回 **ok=True、零偏差**（静默放行）
- 定性：属"判别力收窄/新增假通过面"（修复前这些槽零特异性——正确也报），非把能用的检测弄坏
- 更严修法（评审者给出）：保留候选 VA 集合并要求 `bin.va ∈ 候选集`

Ruling: 立为 Task 6 R=2 修复 — 工具定位"最终裁判"，对真重载系静默假通过正是本架构要挡的失效模式；修法有界（评审者已给出）— 若错：一次多余修复轮（代价小）
Task 5: R=2 re-review ADDRESSED (R2-1, Q1 两洞仍封死, 场景③放行, 0 新增破环)
Task 5: complete (commits 50ecae6f4..f87ea44b7, 2 fix rounds, all reviews clean)

独立验证高点：
- AST 比对：唯一功能差异就是 _SURFACE_METRICS 少一个元素（恰为一行降级），其余全是 docstring（已同步 R=2 理由与实测数字，无说谎文档）
- Q1 ①：唯一 down=slots（两个比值都在"上升"方向）⇒ 纯粹靠 slots 封死
- Q1 ②：components 只有 ('slots',3,1,'down')；count_denom **不在 components**（实测断言 False）
- 额外探洞 D1-D6（删被覆盖声明/加多余声明/加回冗余/整类消失/删 MI 次视图）全部按预期 blocked
- 不变量：删声明后能 pass 的只有"工具自己 count_health 上升"那一类
- 场景③：正确清理 ⇒ improved/passed/updated=YES；反向守卫（加回冗余）⇒ blocked（未开口子）
- 消费者核查：count_denom/_SURFACE_METRICS/_RATCHET_METRICS 无其他消费者；无 data/status/*.json 基线含 count_denom 键
- 测试：88 passed；测试侧删 0 加 1；删除行仅 2（1 docstring + 1 旧断言被更强断言取代）

延期 minor：Q7 静态守卫字面串（仍开）· Q8 decision=None 时无 ratchet 键（仍开）· Q9 红态不可复现 · 降级后"声明数不得缩小"保护消失（接受面界定为"删除后工具自身 count_health 上升"的删除）

## Task 6 修复轮 R=2 完成

提交：e3afc0998（vtable_verify.py + 测试）· 测试：61 passed（52→61，+9）· VTV_LIVE=1: 64 passed
修法：纯"bin.va ∈ 候选集"**不足**（DestroyEffBase 两个 VA 都在候选集 ⇒ 包含判据仍放行）⇒ 落地为
  候选集保留 + **用 .obj 符号自身参数编码收敛候选集**（idx 参数文本 → mangled 参数后缀，借 vc6_mangler.encode_type）
  + 收敛不了才用包含判据 + 两侧都无 VA 才退回纯名字判据

真机证据：189 表/639 槽，歧义槽 24 个（3.8%，12 name_id）
- 表 0x56F674 槽0 = DestroyEffBase(char)@0x4C1640；.obj 装 (void) ⇒ **修复前 rc=0/identity=mixed/零偏差 → 修复后 rc=1/slot 0 slot_key** ✓
- 健全性：112 个有真名候选 ⇒ **假报 0**；错装方向 25 例 ⇒ 判死 15

Ruling: 顾虑1（残项 10 例错装仍静默：`_sdtor_*`/`_scalar_dtor` 同签名组，idx 名逐字相同，真符号是 IDA 伪名）— 接受为已文档化局限（不劣于修复前）；消掉需精确 mangled 名→VA 索引（新增数据源）⇒ 记 deferred
Ruling: 顾虑2（**既存 bug**：bin_table_from_image 与 vtable_compare.bin_table 表长上界用 nxt[0]，而 targets 来自 set ⇒ 上界是任意更大表起始非最近者）— 立为独立小任务（两侧同时改 min(nxt)）；本轮不改（只修一侧会让跨实现一致性测试变红）— 若错：表长界定不确定（同 base 不同进程读出 3 槽或越界）
Ruling: 顾虑3（encode_type ptr>0 分支先于 tag ⇒ `struct X*` 编成 PAVX@@ ⇒ 正确重载误报）— 已修（_swap_class_tag + 两形态 + uint 归一 + 回归测试）⇒ 接受
Ruling: 顾虑4（_inherited_alias_hint 收紧）— 接受
Task 6: R=2 re-review ADDRESSED (R2-1 关闭, 0 新增 live 破环)
Task 6: complete (commits 0c6fde7eb..e3afc0998, 2 fix rounds, all reviews clean)

独立验证高点：
- 坐标 ground truth 自证：0x56F668.. 原始字节 [0x4C2030,0x4C2850,0x4C2040,0x4C1640,0x4C2170,0x4D33A0] ⇒ 控制器两个坐标都真（0x56F674 槽0 直装 0x4C1640；0x56F668 槽2 装 0x4C2040 = adjustor thunk 到 0x4C1640）
- ① 0x56F674 槽0 装 (void) ⇒ EXIT=1 slot_key（VA obj=0x4C1660 bin=0x4C1640）✓ ② 同表装正确 (char) ⇒ EXIT=0 ✓
- ③ 0x56F668 槽2 装 (void) ⇒ slot 2 slot_key ✓ ④ 同坐标装正确 ⇒ 无 slot_key ✓
- **健全性**：53 歧义组、以每候选自己真 mangled 名当 .obj 符号 ⇒ 90 可判候选 **假报 0**
- 真机产物 A/B（24 .obj × 真表地址）：21 对偏差集合逐字相同；3 对只多了新增 VA 坐标文本，rc 全同 ⇒ **无净变化**
- R=1 回归：14/14 仍绿；`name_to_va_index` 单值投影契约**逐字未变**（3503 条集合相等；53 歧义名 0 泄漏）
- 24 个歧义槽全部脱离名字判据（resolution 分布 va 34 / candidates 19 / **name 0**）

Ruling: 新增 latent 加固项（`_param_code_variants` 直信 encode_type，对按值未知类型静默回退 'H' ⇒ 后缀嵌套可把**正确**重载收敛到错误候选 ⇒ 误报；真机 53 歧义组中按值非内建参数 **0 例**、90/90 候选假报 0 ⇒ **潜伏未活**）— 裁定**延期**（与 R=1 的 live 假通过面区别对待：R=1 是 24 个真机槽必静默放行，本项真机 0 例）— 修法已记录：把 mangler 不认识的按值标识符改判"编码不可确定"（不收敛）— 若错：未来出现按值未知类型时误报（会有反例可查）

延期 minor（6 条）：
1. 3 个同签名 `scalar deleting destructor` name_id（7 真机槽）⇒ 错装仍静默（不劣于 R=1）；需 per-VA mangled 名索引
2. `:1126` narrowed 收缩到 ≥2 子集时仍用**全集**做包含判据（7 个后缀嵌套组潜伏，已验证不在 24 歧义槽内）
3. `_vc6_mangler()` 副作用 `sys.path.insert(0, ROOT/pipeline/ida)` 污染消费者 sys.path[0] ⇒ 建议 importlib 显式加载
4. 报告 R2.4 枚举口径未写明（评审 90/29 vs 报告 112/25；结论不变）
5. 报告"同 base 不同进程读出 3 或 4+ 槽"**不可复现**（10 次全 bin=2）；`nxt[0]` 风险与 `min(nxt)` 双改建议仍成立（既存）
6. `identity_mode` 把候选集判据计入 'va'（notes 单独留痕）⇒ **Task 8 须知 'va' 现含包含/交集判定**

## Task 8 完成（DONE_WITH_CONCERNS）—— 最后一步

提交：2eb555f09（3 files, +3204：tests/test_vtable_e2e.py · data/status/vtable_e2e_report.json · data/status/vtable_ratchet_baseline.json）
测试：离线 19 passed/8 skipped；PAL3_E2E_LIVE=1 → 27 passed/0 failed；前序 8 套无回退

### 3 个断裂单元双裁判
| 单元 | L1 | .rdata | 判定 |
|---|---|---|---|
| CCBStageShadow | 0/partial=8（matched 9/13）| 不适用（头 0 virtual + ctor 0x511EE0 字节级扫描零 vptr 写 + PDB 成员自+0起）| `l1_broken_rdata_na` |
| PalScriptWaitObj | 0/partial=1 | 结构性缺失（头 0 virtual 但二进制要 vfptr：PDB size8 + RoleCameraCtrl 成员自+8起 + Task4 PMF=8 + 注解把 +0 记成数据成员）| `both_broken` |
| UI3DCtrl | 0/partial=12 | obj 26 槽 vs bin 8 槽（9 偏差）| 见下根因 |

**UI3DCtrl 根因定位**：发射器把 **UIWnd 的 21 个 virtual 整体抄进派生头**，派生类自家 `slot_0`(=ShowWindow@0x445E70) 因占位名不同未被识别为覆写 ⇒ 追加到槽 21 而非覆盖槽 12 ⇒ 从槽 1 起整体错位。表地址两侧互证（注解 0x56ACFC = ctor 0x43D83A `c7 06 fc ac 56 00`）

### ★★ /GR spike（真项目类 AStarPathFinder 探针 vs 二进制真表 0x56A600）
| 项 | 无 /GR | 带 /GR |
|---|---|---|
| 符号 value | 0 | **4** |
| COL | None | **`??_R4AStarPathFinder@@6B@`** |
| COMDAT | 8B | **12B**（COL+2 槽）|
| obj RTTI | — | **+810B** |

**结论 `GR_IS_STRUCTURAL_BLOCKER`**：每表多 4B + 逐槽位移 ⇒ `.rdata` byte-match **结构性不可能**
**建议**：①移除管线 /GR（`cmake/MSVCSettings.cmake:89` · `pipeline/compare.py:69/81` · `pipeline/cli.py:690`）②`vtable_verify.py:161 DEFAULT_PROBE_FLAGS` 的 /GR 也去掉
**未落地**（超出"只创建 test 文件"范围）⇒ 转出工单 **T1**

### ★★ 新增 e2e 归因（需裁定）
`bin_table_from_image` 的**类族一致性判据在 92/189（49%）张真机表上过度截断**
- raw 界定 **1164 槽** vs 族判据 **639 槽** = Task 6 报告发表的"189 表/639 槽"
- ⇒ **Task 6 的真机数字是在被截断的表上算的**
- 双裁判改用 raw 界定作槽数分母并同时记录两者

### _layout_asserts.h 接线（I-3）
方案=发射的 .cpp include 块末尾追加 include（生成器契约"必须在全部类声明之后"；/FI 强包含实测 C2059/C2143/C2118 不可用），按类 `--only` + consistency-only 灰度
**已验证一个单元端到端生效**：CCBStageShadow 生成 rc=0/9 条断言，正相 rc=0，负相 sizeof 1556→1557 ⇒ **C2118** ⇒ `wired_and_enforced`

### 当日基线
棘轮 rc=0 落盘 `data/status/vtable_ratchet_baseline.json`（78 类/841 槽，显式 --baseline）；缺 --baseline ⇒ rc=2（Q2 生效）；mapper 快照漂移 0 ⇒ 今日无需刷新

### Task5 两条归因线索落定在发射器层
- **CEffectSystem** Reset 注解带 `ordinal=8` 却排在声明第 2 位（8 处错位，**混用两套排序**）
- **CGameData** 凭空注入 `virtual ~CGameData(){}` ⇒ 8 声明 vs 7 槽（二进制槽0 是继承的 UIWnd::ShowWindow）

### 转出工单 6 条
T1 /GR 落地 · T2 发射器 include 接线 · T3 表长界定两处 · T4 发射器槽序/虚析构 · T5 完整 loop 运行（会首次把 Task7 的 113 处虚调用转换写进 pal3/src/**）· T6 注解/stage3 潜伏项

### Task7 顾虑a 量测落定
另一契约读法 ≈439–464 处新 stub，而这些间接调用文本**本身可编译** ⇒ 合成 stub **无可编译性收益，只引入字节差异**；确切字节影响待 T5

Ruling: /GR 发现立为**最高优先工单 T1**（`.rdata` byte-match 的结构性阻塞）— 落地需完整 pipeline 运行验证（S2/L1 影响面）⇒ 本会话记录证据与精确落地点，不在本次落地 — 若错：`.rdata` 维度永久不可 byte-match
Ruling: 接受 Task 8 的双记录方案（raw 界定作槽数分母 + 同时记录两者）— Task 6 的 639 槽口径确有过度截断（92/189=49%），族判据缺陷归工单 T3（两侧同修）— 若错：Task 6 数字口径混用
Ruling: UI3DCtrl 根因（发射器整体抄基类 virtual + 占位名不识别覆写）归工单 T4 — 这是真实字节错位，非 Task 8 范围
Ruling: _layout_asserts.h 接线方案（include 块末尾 + 按类灰度）记录为 T2 — 本任务已验证单单元端到端生效（`wired_and_enforced`）

## Task 8 评审结果（两裁定 ✅，无 Critical）

独立复现：离线 19/8skip · LIVE 27/0 · 前序 7 套逐套相同 · 表长普查自写实现重算（189 表/raw 1164 槽/族判据 639 槽/截断 92）逐字相同
✓ 双裁判名副其实（重新解析 UI3DCtrl_object.obj 验证 26 槽 + 26 条重定位名，非只跑一个裁判）
✓ /GR spike 可信（自写探针独立复现：无/GR value=0 无 COL；带/GR value=4 有 COL；自写 PE 读 0x56A600-4=0x3F800000 非指针）
✓ 3 单元判定有证据（CCBStageShadow ctor 0x511EE0 vptr 写零命中；UI3DCtrl ctor `c7 06 fc ac 56 00`@0x43D83A 命中 + 二进制 0x56ACFC 自写读=8 槽 + obj=26 槽且槽1..20 与 ??_7UIWnd@@6B@ 逐槽相同 + 槽21=UI3DCtrl::slot_0 ⇒ T4 根因确认）
✓ 接线 wired_and_enforced 可信（负相输出**只有** C2118 且行号 48 = 被篡改的 sizeof(CCBStageShadow)==1556）
✓ 6 条工单落点真实
TDD 红相：桩掉 9 个纯函数 ⇒ 2 passed/17 failed/8 skipped（与报告"2 passed"精确吻合）；但单 squash 提交无法证明时序

### Important 发现
I-1 要求 5 的 6 条 .rdata 边界只处置 5 条：`identity_mode` 的 `'va'` 现含包含判定（一侧单一 VA、另一侧候选集 ⇒ 包含判据，used_va 置 mode 'va'）在 §5 表**零处置**
I-2 **§5② 的 `nxt[0]` "bug" 不成立**（★纠正控制器先前记录）：唯一生产者 `bin_vptr_targets()` 返回 `sorted(out)`，所有调用点（vtable_verify.py:1765、vtable_compare.py:244）都传有序表 ⇒ `nxt[0]==min(nxt)`，建议的 `min(nxt)` 是**空操作**。真实边界是"**ctor 实写目标落在当前表内部时截短**"：实测 CEffectSystem 0x56F824 有 9 个代码指针（注解亦 9 槽），next target 0x56F844 恰是槽 8 地址，被硬上界截成 8 槽 ⇒ **T3 按原表述改会误导后续会话**
I-3 **§6.2 支撑断言事实错误**："`virtual ~CGameData(){}` 是凭空多出来的一个槽（二进制没有对应槽）"——实测 **0x56B094 槽 5 = 0x44F030 = `CGameData::'scalar deleting destructor'(uint)`，二进制有析构槽**；头里 7 条 virtual 与二进制 7 槽 1:1 对应（含该析构），多出的 `virtual ~` 是**重复注入**（注解已把该槽建模为具名方法 `_scalar_dtor`）⇒ 归因到发射器方向仍成立
I-4 §8.1 称"不变量…CGameData/CEffectSystem 判据可复现"**无据**（测试文件对二者 0 命中）
I-5 `test_live_bin_table_census_...` **硬钉缺陷态** `targets_slots_family_rule == 639`（族判据当前错误输出）⇒ 与 §8.1 自述"不停在当前缺陷状态"自相矛盾，**T3 修好后该测试必红**（尽管一切变好）
I-6 最强归因（UI3DCtrl 槽1..20 抄基类 + 自家 slot_0 被追加到 21）**无断言保护**，只断状态

### Minor
同文件数字矛盾（test:533/:1117 写 87/189，文件头 :33 与报告/实测均 92/189）· 真机套件改写已入库的 vtable_e2e_report.json ⇒ 跑完工作树变脏 · test_live_dual_judge_report_end_to_end 重跑其余 7 条 LIVE 的重活

Ruling: **撤销先前"nxt[0] 表长上界 bug"工单记录** — 评审独立核实其为非 bug（生产者返回 sorted）；真实边界改写为"ctor 实写目标落在当前表内部时截短（CEffectSystem 9→8）" — 若错：T3 按错误表述改会误导
Ruling: Task 8 R=1 修复 I-5（移除 639 硬钉 → raw 界定不变量 + `family_rule <= raw`）+ I-3/I-4/I-1/I-2 文档更正 + Minor docstring 87→92 — 均为被钉死的缺陷态/事实错误，会误导后续工单 — 若错：T3 修复后测试假红

## Task 8 修复轮 R=1 完成

提交：37888beed（2 files, +470/−32）· 测试：离线 19 passed/8 skipped；LIVE 27 passed；跑完工作树干净；前序 7 套逐套同基线
- **I-5**：删 639 硬钉 ⇒ ①raw 不变量 `targets_slots_raw == 1164` ②关系 `0 < family_rule ≤ raw` ③例证自洽；639/76 只留痕。`grep "== 639"` ⇒ 0
- **I-2**：核实 `bin_vptr_targets()` 返回 `sorted(out)`（调用点 vtable_verify.py:1765 / vtable_compare.py:244 都传有序表）⇒ `nxt[0]==min(nxt)`；§5②/T3/文件头/§7 全部改写为**硬上界截短**（CEffectSystem 0x56F824 注解 9 槽逐槽与镜像 dword 同址且 9 个都是代码指针，next ctor 目标 0x56F844 恰是槽 8 地址 `base+8*4` ⇒ 只读到 8 槽）
- **I-3**：§6.2 改正为**重复注入**（二进制 0x56B094 槽 5 = 0x44F030 = `CGameData::'scalar deleting destructor'(uint)` idx 实名 ⇒ 有析构槽；头 7 条具名 virtual 与二进制 7 槽逐槽同序 1:1；多出的 `virtual ~` 是注解已建模 `_scalar_dtor`(ordinal=5) 后的重复注入）；T4 措辞同步
- **I-1**：§5 补第 ⑥ 条（`identity_mode='va'` 含包含判据，不可读作"两侧都有单一 VA"）
- **I-4**：采方案①— 新增 `attribution_evidence()` 机读留痕（JSON 顶层 `attribution` 段 + `render_report` 一行）+ 在 `test_live_dual_judge_report_end_to_end` 逐条断言两条归因；§8.1 无据断言已改有据并显式记录 R=0 此处无据
- **I-6**：加断言（写在既有 LIVE 用例内 ⇒ 条数契约不变）：`??_7UIWnd@@6B@`(21 槽) vs `??_7UI3DCtrl@@6B@`(26 槽) 逐槽比 ⇒ 基类块同下标对齐、差异**恰为 `[2,15,16]`**（slot_2/3/4 与基类同名 ⇒ 在位覆写）、`obj[12]` 仍是 `UIWnd::ShowWindow`（未覆盖）、`UI3DCtrl::slot_0` 在 `index == 21`（**追加**）
  TDD 红→绿：按评审**字面**建议先写 `obj[1:21] == base[1:21]` ⇒ 实测 **AssertionError**（3 处同名覆写，字面形态不成立）⇒ 按实测收敛后 PASS
- **Minor**：87/189 → 92/189（两处，`grep "87/189"` ⇒ 0）；`run_e2e(write=False)` 默认 + `out_path` + CLI `--no-write` ⇒ 跑完整真机套件后入库 JSON sha256 **前后不变**（29fa63a5…）且工作树无 modified tracked 文件

Ruling: 顾虑1（I-6 与 I-5 原则表面张力：I-6 钉住发射器当前形态）— 已在代码注释/§11.3 写明"是发现的钉子，T4 时同步改"，且其中"具名 7 条与二进制 7 槽逐槽同序"等断言不依赖缺陷是否修好 ⇒ 接受
Ruling: 顾虑2（0x56F844 字节层面本身歧义：既是 0x56F824 槽 8 地址、也是另一张 ctor 实写表的槽 0，共享同一 dword）— Task 8 只量化+留痕+断言判据，**不裁定谁对**（裁定属 T3）⇒ 接受；**注意"8 vs 9 槽"不是纯字节可判** — 记入 T3
Ruling: 顾虑3（raw 不变量 `== 1164` 钉的是观察口径非缺陷值）— 若 T3 改变表长语义需同步更新 ⇒ 记入 T3

## Task 8 修复轮 R=1 复审结果

实跑：离线 19/8skip · LIVE 27/0 · 前序 7 套逐套同基线 · 裸 PE 独立复证（0x56B094 7 槽槽5=0x44F030 代码指针；0x56F824 槽0..8 全代码指针、槽8=0x4C6260、0x56F844−0x56F824=32=8*4）· 真机套件跑完 JSON sha256 不变 + 工作树干净
逐条：I-5/I-2/I-3/I-1/I-4/I-6/M-1/M-2 **全部 ADDRESSED**
- I-4 实证：测试文件 CGameData/CEffectSystem 由 0 命中 → **23/13 命中**
- I-6 独立重发射：base 21 槽、diff 恰 [2,15,16]、obj[12] 未被覆盖、slot_0 在 index 21 ✓

### ⚠️ 新增破环（1 项，建议 R=2 一行修）
`tests/test_vtable_e2e.py:1372-1374` 新增 `assert c['examples']` + 逐例 `assert e['family_rule'] < e['raw']`
⇒ **等价于本次被删掉的 `assert c['truncated_family_rule'] > 0`**——要求族判据截断缺陷**继续存在**
⇒ 而同提交 `:40` 自称"T3 修好族判据后两者应相等" ⇒ **T3 落地后 examples 为空、该 LIVE 用例必红**（尽管一切变好）
⇒ **I-5 的危害换断言重新引入**，且与同提交 docstring 自相矛盾
修法：去掉非空断言，或改为"examples 非空时逐例自洽"的**条件式**关系断言

延期 minor：raw==1164 钉观察口径 · 发射器形态钉子待 T4 同步 · `_base_raw()` 未包 try/except · bin_table_census docstring「189 表/92 注解表」不准 · I-1/I-2/I-3 正文更正落在 gitignore 区 · 入库 JSON 末尾无换行

Ruling: Task 8 R=2 收口 — 该破环与 I-5 同害（会在 T3 修好后为正确改动报红），且修法为一行条件式断言 — 若错：一次多余修复轮

## Task 8 修复轮 R=2 完成

提交：9479c3a7e（tests/test_vtable_e2e.py +110/−88）· 测试：离线 19/8skip · LIVE 27/0 · 前序 7 套同基线 · 入库 JSON sha256 前后同 29fa63a5…
- **I-5 二次收口**：删 `assert c['examples']`，只留条件式 `for e in c['examples']: assert e['family_rule'] < e['raw']`；docstring 第③条同步"条件式（为空同样合法）"；可执行非空断言 0 处
  TDD 双向：模拟 examples==[] ⇒ 改前 **RED**（AssertionError 打印 'examples': []）、改后 **GREEN**；当前真实 examples 非空（8 条）⇒ 改前改后皆 GREEN
- **Minor（已做）**：`_base_raw()` 原未包 try/except ⇒ 缺文件让 run_e2e 抛异常；改为 `_cg_record()/_ce_record()` + `_degraded_or(cls, fn)` 包裹，失败返回 `{'cls','degraded':True,'error'}` 留痕
  TDD：HEAD 对照 **RAISED FileNotFoundError** ⇒ 改后 **DEGRADED**；重构等价性：新输出与入库报告 attribution 段逐键比对 **0 差异**

Ruling: 顾虑4（降级路径断言是"degraded 即不可判定并显式报错"，还是"缺文件也算通过"）— 接受实现者的保守选择（只把"崩溃"改成"降级+留痕（报告能落盘说明原因）"，LIVE 断言仍要求硬键 ⇒ 缺文件**失败而非静默通过**），符合本项目反静默假通过原则 — 若错：缺文件时 LIVE 红（而非静默绿），是可接受的保守方向
Ruling: 顾虑1（`targets_slots_raw == 1164` 仍是观察口径硬断言）— 记入 T3 同步项（与 §11.3 顾虑3 一致）— 若错：T3 改表长语义后测试假红
Ruling: 顾虑2（降级记录不含 bin_slots 等硬键）— 与顾虑4 同一裁定：保守方向，不制造静默假通过 — 接受

## Task 8 R=2 复审结果 —— 8 任务全部完成

R2-1 ADDRESSED：可执行断言 0 处（grep 2 命中分别在 docstring 与 # 注释，均为反面引用；可执行引用只剩 :1395 for 循环）
  双向实测（独立驱动，还原 sys.path 避免 symlink 根污染）：
  - HEAD / examples 非空 → GREEN；HEAD / examples==[]（模拟 T3 修好）→ GREEN
  - R=1 对照 / examples 非空 → GREEN；R=1 / examples==[] → **RED**（AssertionError 'examples': []）
  ⇒ 修复前"T3 落地必红"为真、修复后双向不报红，I-5 危害解除
R2-2 ADDRESSED：STRUCTS 指向不存在目录 ⇒ 不再抛异常，返回 degraded 记录；同条件 R=1 副本 → RAISED FileNotFoundError（确认原发现为真）
  传播面：render_report 不崩；打桩重型阶段后 run_e2e 不抛异常且 attribution.*.degraded=True

新增破环：无
- 仅 1 file；入库 JSON sha256 仍 29fa63a5…；tracked 工作树干净
- **重构等价性**（88 行缩进变换）：token 级 `_cg_record` 348/348 完全相同；`_ce_record` 392/392 仅末位 NEWLINE 之差
- 健康路径 `attribution_evidence()` 与入库报告 attribution 段逐键 **0 差异 / EQUIVALENT**
- 实跑：离线 19/0/8skip；LIVE 27/0/0；前序 7 套逐套同基线全 0 failed
- 交叉引用核查：`_base_raw`/`_cg_record`/`_ce_record`/`_degraded_or` 全为内部局部符号；仅 run_e2e:1029 消费返回值

延期 minor（5 条，均非阻塞）：`targets_slots_raw == 1164` 观察口径硬断言（T3 同步项）· 降级记录不含 bin_slots 硬键（保守方向已披露）· 两层降级粒度未合并 · render_report 对降级打印 None 占位（cosmetic）· `_degraded_or` 捕获裸 Exception（与既有同款）

★★ 复审者的方法学坑（**重要，后续复审必读**）：把 R=1 副本放 /tmp 且 tools/pipeline 用 symlink 指向真仓时，模块级 `sys.path.insert` 使 `vtable_verify` 经 symlink 路径导入 ⇒ census 变成 659/90 且 wine 发射失败（obj_slots=None）——**纯属 staging 假象**，干净单模块进程稳定复现 639/92 与 obj_slots=8。后续复审做同款对照务必在加载后还原 sys.path。

## 全分支最终评审结果（裁定 1 ✅ · 裁定 2 ✅ · 裁定 3 ❌）

独立验证（全部实跑）：8 套测试逐数吻合（35/38/68/73/88/61+3skip/35/19+8skip 全 exit 0）· 真机 e2e 27/0/0 · 表长口径独立重算（raw 187 表/1164 槽、族判据 187 表/639 槽、截断 92 张）逐字吻合 · CEffectSystem raw=8/注解=9 ✓ · CGameData 7 代码指针、槽5=0x44F030 ✓ · `/GR` 二进制侧 0x56A600−4=0x3f800000 非 COL ✓ · RTTI 串恰好 6 条全 CRT/STL ✓ · 0x56AB28 槽2 jmp 目标 0x423860 ✓
环境事实：本机 pytest 必然崩溃（5.4.1.dev + py3.10 断言重写），8 套均自带 runner ⇒ **"全绿"成立但非 pytest 口径**

### 裁定 1（集成一致性）✅
词面适配/契约变更均实测可组合：`normalize_bin_slots` 删 va_of 后仓内全部调用点参数兼容；`'func'↔'fn'` 经适配器；Task1→5（match_key 索引）、Task2→6（classify_slot）、Task2→3（原始文本强制）、Task5→3（键归一）、Task4/5/6→8（LIVE 27/0）**全部为真实功能调用非声明式导入**
- I-1（Important）：**无端到端驱动器** — tools/pipeline/Makefile/CI 中无脚本串联 8 个工具（grep 0 命中）；实际串联仅 Task5 库级 import + Task8 测试 harness；规格 §5 数据流未被实例化
- M-1：飞行前冲突扫描 2 条边与代码不符（Task2→1 / Task7→1；实测 T1 只 import re/dataclasses，stage3 不 import T1/2/3）
- M-2：两个已披露 minor 仍有效（`--struct` 静默伪候选；CLI 前缀拒写误拒兄弟目录）

### 裁定 2（交付完整性）✅（缺口均已诚实记录）
7 条约束：C1 ✅（`__vftable/vfptr/vtable` 0 命中）· C2 ✅ · C3 ✅ · C4 ✅ · C5 ✅ · **C6 ⚠️ 部分**（转换+fail-closed+记账**代码**齐备，但记账产物 `data/status/vtable_transform_failures.md` 在 HEAD **不存在**，`git log --all` 0 提交且未被 gitignore）· **C7 ⚠️ 部分**（生成器默认开，但 `_layout_asserts.h` 在 pal3/ 下 **0 处 include** ⇒ 今日零断言生效；规格点名 `--no-layout-assert` 全仓未实现）
**终极目标未达成且缺口被诚实记录**：独立复证全部载体证据（6 条 CRT/STL `.?AV`、`0x56A600-4=0x3f800000`、生产管线**确实**带 /GR，台账 4 个落点**行号逐字准确**）⇒ **T1 最高优先**；task-8-report §2 明确写入"保留 /GR 则**不得**在任何文档写 vtable byte-match" ⇒ **诚实性满分**
T1-T6 恰当、落点具体、覆盖全部未落地缺口 ✅
- I-2（Important）：**Task 6 评审 I3（"报告 §2.1 输出删减"）无任何处置** — 不在修复项、不在延期清单、不是工单；其余全部评审发现项均有明确落点 ⇒ 唯此一条被静默丢弃
- M-3：C6 记账产物未交付（已记录无隐瞒）

### 裁定 3（诚实性）❌

**★ Critical：Task 8「端到端 L1 裁判」未在生产口径上运行，却声称"与生产 L1 同一口径"**
- 声称：`tests/test_vtable_e2e.py:454-455`「与生产 L1 同一口径：`compare_pal3.PROBE_FLAGS`（`/nologo /TP /c /W3`，**不含 /O2、不含 /GR**）」；task-8-report §1 同；§2 理由① 据此断言「移除 /GR 后 L1 口径不变」；台账 :308 亦裁定「L1 比对 .text 不受直接影响」
- 反证（三处独立可复跑）：① 生产 `match` 唯一调用点 `pipeline/cli.py:691` 传 `--flags "/nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd"` ② 生产 L1 基线 `data/status/s4_baseline.json` 的 flags **恰含 /O2 与 /GR** ③ 入库 `vtable_e2e_report.json` 三单元 `l1.flags` 实为 `['/nologo','/TP','/c','/W3']`
- ⇒ **e2e 的 L1 判词不是生产口径结果**；`PROBE_FLAGS` 只是 compare_pal3 的 probe 默认值（`HYPOTHESIS_FLAGS` 才含 /O2/GR）
- 后果：非优化无 RTTI 产物与 /O2 原二进制逐字节比 ⇒ L1 近乎结构性必为 0 ⇒ **该维度不具判别力**；且 T1 的「移除后 L1 口径不变」**是错的**（移除 /GR 必然改变生产 L1 标志，L1 基线须**重测**）
- 缓解：`.rdata` 裁判（真正的 vtable 裁判）走独立 `/Od` 探针，**不受影响且证据为真**；台账 :627 另要求 T1 落地须完整 pipeline 验证 ⇒ 风险有界
**Minor**：台账 :324/:326「控制器已补提交」与 :381 撤销并存（可误导线性读者）

**诚实性正面（独立复证）**：/GR 未粉饰且自设"不得写 byte-match"红线 ✅ · 潜伏 vs 引爆区分正确（6 个 CEffTrack* 实测均无 .cpp ⇒ 潜伏；4 个 .cpp 实测存在 ⇒ 可达）✅ · I-5 硬钉被三轮抓到并最终改为条件式（可执行非空断言 0）✅ · `== 639`/`87/189` 0 残留 ✅ · CGameData 更正与 `nxt[0]` 撤销均为真更正 ✅

**总体结论：需修复 2 项后交付**（1 Critical + 1 Important）+ 4 Minor 建议

Ruling: 全分支最终评审的 Critical 立为**收口修复轮** — L1 口径失实是真实的过度声称（且污染 T1 影响面论证）；修法明确（改措辞 + 按生产口径重跑 3 单元 L1 + 刷新报告 + 更正台账/report + T1 写明"移除 /GR 会使 L1 基线变动须重测"）— 若错：交付物带错误口径
Ruling: Important（Task 6 I3 未处置）— 一并收口（补记或修复）
Ruling: 4 Minor — 一并收口（无驱动器声明/扫描边更正/--struct 报错/CLI 拒写精确化/台账撤销标注）

## 全分支最终评审收口修复轮（R=3）完成

提交：`244f0ea12`（4 files：`tests/test_vtable_e2e.py` · `tests/test_vtable_sig_infer.py` · `tools/vtable_sig_infer.py` · `data/status/vtable_e2e_report.json`；本报告/台账在 `.superpowers/sdd/`（gitignore）⇒ 不入库，与本计划历轮同例）
测试：离线 **22 passed / 0 failed / 8 skipped** · LIVE **30 passed / 0 failed / 0 skipped** · 前序 8 套 **35 / 38 / 71 / 73 / 88 / 61(+3 skip) / 35 / 22(+8 skip)** 全 0 failed（71/22 = 本轮新增测试后的计数：sig_infer 68→71、e2e 19→22）· 跑完工作树仅 4 tracked 文件 M

### ★Critical（L1 口径失实）—— ADDRESSED
- **病灶层**：口径属 harness 的**参数层**（非编译器/IDB/codegen）；消费者 = `judge_l1` 传给 `compare_pal3.compare_units` 的 `flags` 实参 + 报告 `units[*].l1.flags`/`meta.l1_flags`
- 修法：`judge_l1(unit, ctx=None, flags=None)` 默认走 `production_l1_flags()`（读 `s4_baseline.json.flags`；缺失退回与 `cli.py:690` 逐字相同的兜底常量，**不退 probe 口径**）；判词加 `caliber`/`flags_source`；`run_e2e` 双口径并列（`l1` 生产 / `l1_probe_default` probe）；措辞更正（docstring + 文件头）
- **按生产口径重跑 3 单元**（同一 harness 两套 flags 并列实测）：CCBStageShadow **2/6** vs probe 0/8 · UI3DCtrl **2/10** vs probe 0/12 · PalScriptWaitObj 0/1 vs 0/1
- **刷新** `data/status/vtable_e2e_report.json`：sha256 `29fa63a5…` → **`e67d1278af21`…**；`meta` 同时记录两套 flags + 来源 + "不可混读"注
- **连带更正**：task-8-report §1/§2 建议①（"移除后 L1 口径不变" **为假**）· 台账 `:322`（原 `:308`，已在本文件内联更正）· **T1 工单**写明"移除 `/GR` 会改变生产 L1 编译标志 ⇒ **L1 基线须重测**"· `gr_spike_analysis` 建议文本同警告
- **定性更正（重要）**：原"L1 近乎结构性必为 0 ⇒ 该维度不具判别力"是**口径错误的产物** —— 生产口径下 CCBStageShadow 与 UI3DCtrl 各有 **2 条函数体逐字节全同**，该维度**有判别力**；且 `symbols`/`unmatched` 亦随口径变（旧"matched 9/13"与"matched 9/10"不可混读）
- **TDD 红→绿**：HEAD 副本三轴 RED（`/O2` False、`/GR` False、`≠PROBE_FLAGS` False；doc 含失实短语；两个 helper 不存在）⇒ 改后 GREEN；新增离线测试 3 条
- **边界**：`.rdata` 裁判走独立 `/Od` 探针，**不受影响**（评审已复证其证据为真，本轮未改动）

### Important I-2（Task 6 评审 I3「报告 §2.1 输出删减」无处置）—— ADDRESSED
- `task-6-report.md §2.1` 补全完整 `--list` 输出（`--list` = **4 张**表、`--cls D --list` = **3 张**表；原各只贴最后 1 张）+ 更正注（含三视图 `vbtable=[-4,24]`、`deleting_dtor` vs `composite` 对照）

### Minor —— 全部 ADDRESSED
1. **无端到端驱动器** → **显式声明**（评审给出的第二选项）：落点写入 `tests/test_vtable_e2e.py` 文件头（**已入库**）+ 台账 —— 无独立驱动器脚本；串联 = ①库级 import 链（T1/T2/T3→T5 `vtable_decl_check.py:113/:122/:134`；T2→T6 `vtable_verify.py:119`；T2→T3 `vtable_sig_infer.py:102`）②`run_e2e()`（T4/T5/T6 + L1 裁判）；**T7 不由本 harness 驱动**（codegen stage）⇒ 不得声称"8 工具全链"
2. **飞行前扫描 2 条假边** → 台账表划除 `Task2→Task1`/`Task7→Task1` + 表注 M-1 给实测证据（`vtable_slot_order.py:47-48` 只 import `re`/`dataclasses`；`stage3_cleanup.py:7-17` 不含任何 vtable 工具 import，名称解析读注解 `vtables[0].slots`+`methods` `:184-187`）；补记两条真实边 T2→T5 `:122` / T2→T6 `:119`
3. **`--struct` 静默伪候选** → `tools/vtable_sig_infer.py` 新增 `_slot_evidence_kind()` 门：无槽证据 ⇒ `SystemExit` **rc=1**（原静默 exit 0 + 键 `""` 伪候选 `? unknown _slot()`）；含 `slots` 时行为不变。TDD：HEAD RED（stdout 含 `"methods_pending": {"":`）⇒ 改后 GREEN
4. **CLI 前缀拒写误拒兄弟目录** → `startswith` → `_is_under_truth_source()`（`os.path.commonpath` 分量级）：`data/annotations/**` 仍拒写、`data/annotations_bak_probe/**` 放行落盘。TDD 双向
5. **台账撤销标注** → `:344`「控制器已补提交」与 `:346`「…入库」加注"已被 `:401`（评审引用 `:381`，本轮新增表注 M-1 前的位置）的『更正 M5』撤销"

Ruling: R=3 收口轮全部落地（1 Critical + 1 Important + 4 Minor）—— Critical 的修法由**代码（口径改为生产 match 口径 + 双口径留痕）+ 实测三单元重跑 + 报告刷新 + 措辞/台账/T1 同步**四件套构成，且 TDD 双向可复跑 — 若错：入库报告仍带错误口径
Ruling: 8 任务计划（T1..T8）至此**全部完成收口**；剩余未落地项仍为**转出工单 T1-T6**（T1 最高优先），本轮只改其影响面论证，**未改**任何管线/cmake/compare flags
Ruling: 顾虑（`production_l1_flags()` 以 `s4_baseline.json` 为权威来源，而该文件会被 ratchet 回写）—— 接受：若某次基线被写成 probe 口径，断言 ②③ 会让 LIVE/离线**响亮报红**（非静默降级），这正是反静默假通过的方向 — 若错：口径随基线漂移，但有红灯兜底

### R=3 提交后复核
- **入库报告可复现**：重新 `--e2e --out /tmp/repro_report.json` 与入库 JSON 逐键比对 ⇒ 除 `generated_at` 外**完全相同**（`REPRODUCIBLE: True`）
- **sha256 实测**：`29fa63a59c77…`（`git show HEAD~1:…`）→ `e67d1278af21…`（工作树）
- **工作树**：LIVE / `--e2e` / `--e2e --out /tmp` 三种运行后均无 modified tracked 文件；`data/annotations_bak_probe/` 无残留
- **提交**：`244f0ea12` 仅 4 文件（`git diff --cached --name-only` 核对）
