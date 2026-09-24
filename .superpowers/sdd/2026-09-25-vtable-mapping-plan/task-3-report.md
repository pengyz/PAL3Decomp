# Task 3 实现者报告 —— 候选签名生成器（provenance + 序言分析）

日期：2026-09-25
简报：`.superpowers/sdd/2026-09-25-vtable-mapping-plan/task-3-brief.md`
规格：`docs/superpowers/specs/2026-09-25-vtable-mapping-design.md` §4.2（组件 1）
**状态：DONE_WITH_CONCERNS**
**提交：`fd2305f05`**（实现+测试+金样本探针）
**报告位置说明**：`.superpowers/sdd/` 被 `.gitignore` 忽略（Task 1/2 报告同此状态）⇒
本报告**只落盘不入库**；代码证据全部在 `fd2305f05` 里。
一行测试摘要：**新 58 passed / 前序 35+34 全绿（无回退）· 金样本 39 条对真机 objdump 逐指令自证 0 不一致**

---

## 0. 交付物

| 文件 | 说明 |
|---|---|
| `tools/vtable_sig_infer.py` | 候选签名生成器（1423 行；证据**只**来自原始指令字节） |
| `tests/test_vtable_sig_infer.py` | 58 条测试（C-1~C-6 · Ruling 1-6 · A/B/C 分级 · /O2 esp 形态 · methods_pending 旁路） |
| `data/status/_vtable_sig_probe_20260925/{rw1..rw4,opt1,opt2}.cpp` | 本轮新增探针源（返回宽度 / f32-f64 / bool / sret 阴性 / 真实项目开关） |
| `data/status/_vtable_sig_probe_20260925/README.md` | 探针出处 + 复现命令 + 实测要点 + 已知缺口 |
| `data/status/_vtable_sig_probe_20260925/verify_fixtures.py` | 金样本**自证**脚本：重编译探针 + 与测试夹具逐指令比对（0 不一致） |
| `.superpowers/sdd/2026-09-25-vtable-mapping-plan/task-3-report.md` | 本报告 |

**无子代理**：本任务全程未分发任何子代理（符合"无子代理契约"）。

**纯新增**：不触碰 annotation/apply/export/codegen/stage* ⇒ 无管线层改动面；
`methods` 真相源**只读**（`build_methods_pending` 深拷贝输入后新增旁路字段）。

---

## 1. 交付 API（供 Task 5 消费）

```python
from vtable_sig_infer import (
    SigEvidence, infer_signature, infer_address_record, find_icf_groups,
    build_methods_pending, iter_candidates, analyze_call_sites,
    param_class_equiv, param_class_family, body_key, sanitize_pe_relocs,
)

ev  = SigEvidence(addr='0x4C5D50', name='f', symbol='?f@C@@UAEHH@Z',
                  disasm=objdump_text,              # **必须**是原始反汇编文本（Ruling 1）
                  call_sites=(objdump_text_of_calls,))     # 可选旁证
c   = infer_signature(ev)          # SignatureCandidate | None（合成槽 ⇒ None）
rec = infer_address_record('0x4C5D50', [ev1, ev2])   # 一地址多候选（ICF）
pend = build_methods_pending(struct_json, [rec])     # methods 原样不动，新增 methods_pending
for addr, cand in iter_candidates(pend): ...          # Task 5 遍历
```

### `methods_pending` 旁路 schema（本任务定义，Task 5 契约）

```json
"methods_pending": {
  "0x004C5D50": {
    "candidates": [{
      "signature": "int __thiscall f(?)",
      "convention": "__thiscall", "arity": 1, "arity_is_lower_bound": false,
      "return_kind": "i32",
      "params": [{"slots": 1, "class_candidates": ["bool","f32","i8","i16","i32","ptr"],
                  "determined": false}],
      "variadic": false, "grade": "A",
      "features": ["ecx_this","ambiguous_param_class"],
      "notes": ["ecx_this: ...", "ambiguous_param_class: ..."],
      "evidence": {"ret_bytes": 4, "bare_ret": false, "stack_slots": 1, "read_slots": 1,
                   "reg_arg_count": 0, "this_on_stack": false,
                   "param_class_undetermined": true, "hidden_param_suspicion": false,
                   "cc_provisional": false, "call_site_consistent": null},
      "slot_kind": "fn", "source": "disasm"
    }],
    "icf_folded": false, "ambiguous": false, "skipped": false,
    "slot_kind": "fn", "features": [], "notes": [],
    "conflicts": []
  }
}
```

* 键格式 `'0x%08X'`，与真相源 `data/annotations/structs/*.json` 的 `methods` 键**逐字同形**
  （实测 3398 个 methods 键全部 `0x` + 8 位大写十六进制）。
* **多候选**：`candidates` 是列表（C-5：ICF 折叠后一地址对多签名）。
* **冲突不覆盖**：`methods[addr].signature` 与候选不一致 ⇒ 只写 `conflicts`，真相源不动。
* 合成槽地址 ⇒ `candidates: []` + `skipped: true`（T2↔T3 契约"T3 消费跳过合成槽"）。

---

## 2. 分级实现（spec §4.2 逐字）

| 级 | 判定式（`infer_signature` 末尾） |
|---|---|
| **A** | `arity` 非 None ∧ 约定已证（非推定）∧ 无隐藏参数嫌疑 ∧ 无 ICF ∧ **返回宽度已知** ∧ 约定非推定 ∧ 非下界 |
| **B** | 上述任一：缺返回宽度 / `hidden_param_suspicion` / `sret_ambiguous` / ICF 折叠（`_cap_grade`）/ 约定系推定（`cc_provisional`）/ `arity_is_lower_bound` |
| **C** | `arity is None` 或约定不可证：变参 · cdecl 读集为空 · 证据不足（Ruling 2）· esp 跟踪中断 |

**A 级不保证参数等价类**：`param_class_undetermined` 独立标记（C-5/C-6 实测 callee 字节
分不出 int/指针/float/BOOL）⇒ A 级只保证"约定 + 个数 + 返回宽度"（spec 措辞逐字）。
签名文本对未定等价类渲染 `?`（例 `? __thiscall unused(?,?)`），**不编造类型**。

---

## 3. C-1~C-6 覆盖情况（逐条 → 测试 → 实测证据）

| 用例 | 缺陷 | 本任务行为 | 测试 | 实测证据（真机 MSVC6） |
|---|---|---|---|---|
| **C-1** | `void S::unused(int,int){}` 读集 ∅ ⇒ 推 0 参（真值 2） | `ret 8` ⇒ `stack_slots=2` ⇒ arity 2 + `hidden_param_suspicion`（槽数 ≠ 参数个数：double/int64/结构占双槽）⇒ **B 级**，签名 `? __thiscall unused(?,?)` | `test_c1_unused_params_are_recovered_from_ret_n` | `?unused@S@@UAEXHH@Z`：11 字节本体、读集 ∅、`c2 08 00` |
| **C-2** | `__fastcall` 无规则分支；callee/调用点/vtable 三层全无感 | 新增 fastcall 分支：**edx 入口实参**（溢出 `mov %edx,-8(%ebp)` 或直接作源 `mov %edx,0x4(%ecx)`）+ 裸 ret 亦可 ⇒ 成员 fastcall = ecx:this + edx:首参 + 栈其余；arity = 1 + `ret N/4` ⇒ 真值 2；调用点只作对账（push=1 与 callee 栈槽 1 一致） | `test_c2_fastcall_detected_from_edx_entry_spill` · `test_c2_call_site_alone_would_say_one_arg` · `test_ruling3_bare_ret_fastcall_is_still_fastcall` · `test_ruling3_thiscall_must_not_be_misread_as_fastcall` | `?freg@S@@UAIXHH@Z`：`mov %edx,-8(%ebp)`；调用点 `push $2; mov $1,%edx; lea -4(%ebp),%ecx` ⇒ push=**1** |
| **C-3** | `__cdecl` 成员 this 在栈 ⇒ 读集计成首参（真值 1 推 2） | 识别"裸 ret + 无 ecx 证据 + 首槽值被解引用（对象访问）" ⇒ `this_on_stack` 并**扣除首槽**；调用点 push 期望 = arity + this ⇒ 两侧一致于**正确**值 | `test_c3_cdecl_member_this_on_stack_is_deducted` · `test_c3_cf2_three_read_slots_minus_this_is_two_params` · `test_c3_call_site_push_count_two_confirms_the_wrong_answer_without_the_rule` | `?cf@Xc@@UAAXH@Z` 读 `[ebp+8]`,`[ebp+0xc]`；调用点 `push 1; push this` ⇒ push=**2** |
| **C-4** | 变参无 `...`；mangling 特征写错（`QAA` 匹配不到） | 识别 `ZZ` 结尾（虚变参 `UAA…ZZ`）⇒ `variadic=True` + 强制 `__cdecl` + arity `None` ⇒ **C 级**，签名含 `...` | `test_c4_variadic_is_recognized_and_graded_c` · `test_c4_non_variadic_is_not_flagged` | `?log@S@@UAAXPBDZZ`：裸 `ret`、读集 ∅ |
| **C-5** | 空体 COMDAT 字节相同 ⇒ 一地址多签名；`methods[addr]` 放不下 | 地址记录 = **候选列表** + `find_icf_groups` 同体分组 + ICF 时 `icf_folded/ambiguous=True` 且**降级到 B**（不得给 A）；`param_class_undetermined` 恒标 | `test_c5_identical_bodies_are_detected_as_one_icf_group` · `test_c5_one_address_may_carry_multiple_signatures` · `test_c5_single_evidence_address_is_not_marked_icf` · `test_c5_int_and_pointer_callee_bytes_are_indistinguishable` | e1 `?o(int)/?o(void*)/?o(float)` 三体**13 字节完全相同**；s1 `?idi/?idp` 亦逐字节相同 |
| **C-6** | BOOL 与 int 字节不等价（+5B 物化） | ① callee 侧恒标 `param_class_undetermined`（候选类含 `bool` 与 `i32`）② 调用点 `analyze_call_sites` 检出 `setcc` 物化 ⇒ `arg_classes=('bool',)` ③ 等价类表：`param_class_equiv('bool','i32') is False`，char/short 独立，`i32`≡`ptr` 但**不可断言** | `test_c6_callee_cannot_distinguish_bool_from_int` · `test_c6_bool_is_not_byte_equivalent_to_int` · `test_c6_char_and_short_are_separate_classes_too` · `test_c6_bool_materialization_is_visible_at_the_call_site` · `test_bool_return_is_distinct_from_char_return` | b1 `?fb`/`?fi` 本体逐字节相同；`p->fb(i)` = `xor; cmp; setne %al; push`（+5B） |

**Ruling 1-6 → 实现的映射**

| Ruling | 实现 | 测试 |
|---|---|---|
| 1 传原始文本 | `SigEvidence.disasm` 非 `str` ⇒ `TypeError`；内部 `parse_disasm_report(原始文本)` + `classify_slot(SlotEvidence(instructions=原始文本))` | `test_ruling1_disasm_must_be_raw_text` · `test_ruling1_empty_text_is_not_silently_a_zero_arg_fn` |
| 2 `fn` 必查 notes | 输入非空但解析 0 条 ⇒ `insufficient_evidence` ⇒ **C 级 + 痕迹**（不当"0 参 void"） | `test_ruling2_insufficient_evidence_is_flagged_not_defaulted` · `test_ruling2_genuine_fn_without_notes_still_infers` |
| 3 fastcall 分支 | edx 入口（溢出 / 作源）+ 裸 ret 形态 | 见 C-2 四条 |
| 4 cdecl this 在栈扣除 | 首槽值被解引用 ⇒ `this_on_stack`；thiscall **不得**再扣（阴性） | `test_c3_*` · `test_ruling4_thiscall_must_not_deduct_a_phantom_this` · `test_ruling4_bare_ret_thiscall_zero_args_vs_cdecl_unknown` |
| 5 BOOL 单独成类 | 等价类表 + 返回侧 `setcc` ⇒ `RET_BOOL` | `test_c6_*`（4 条） |
| 6 sret 隐藏首参 | 单基址寄存器 ≥9 字节连续 store-through + eax 末次载入首槽 ⇒ 扣除；多基址 ⇒ `sret_ambiguous` **不猜**（降级 B） | `test_ruling6_sret_hidden_first_param_is_deducted` · `test_ruling6_non_sret_is_not_flagged` · `test_sret_confirmed_including_zero_arg_form` · `test_sret_ambiguous_is_flagged_not_deducted` · `test_sret_negative_small_pointer_write_stays_grade_a` · `test_sret_negative_void_pointer_param` |

---

## 4. 测试输出（逐字）

```
$ python3 tests/test_vtable_sig_infer.py
PASS test_bool_return_is_distinct_from_char_return
PASS test_broken_esp_tracking_yields_grade_c
PASS test_c1_unused_params_are_recovered_from_ret_n
PASS test_c2_call_site_alone_would_say_one_arg
PASS test_c2_call_site_crosscheck_is_consistent_with_callee
PASS test_c2_fastcall_detected_from_edx_entry_spill
PASS test_c3_call_site_push_count_two_confirms_the_wrong_answer_without_the_rule
PASS test_c3_cdecl_member_this_on_stack_is_deducted
PASS test_c3_cf2_three_read_slots_minus_this_is_two_params
PASS test_c4_non_variadic_is_not_flagged
PASS test_c4_variadic_is_recognized_and_graded_c
PASS test_c5_identical_bodies_are_detected_as_one_icf_group
PASS test_c5_int_and_pointer_callee_bytes_are_indistinguishable
PASS test_c5_one_address_may_carry_multiple_signatures
PASS test_c5_single_evidence_address_is_not_marked_icf
PASS test_c6_bool_is_not_byte_equivalent_to_int
PASS test_c6_bool_materialization_is_visible_at_the_call_site
PASS test_c6_callee_cannot_distinguish_bool_from_int
PASS test_c6_char_and_short_are_separate_classes_too
PASS test_cdecl_member_shape_confirmed_across_probe_tus
PASS test_deterministic_output
PASS test_grade_a_fp_return_width_when_size_is_visible
PASS test_grade_a_narrow_returns
PASS test_grade_a_requires_return_width_evidence
PASS test_grade_b_when_fp_return_width_is_ambiguous
PASS test_grade_b_when_return_width_unobservable
PASS test_grade_b_when_slot_count_cannot_be_mapped_to_param_count
PASS test_grade_c_for_variadic_and_unknown
PASS test_i64_return_from_sign_extend
PASS test_infer_address_record_survives_pe_coff_reloc_text
PASS test_infer_does_not_crash_on_pe_coff_reloc_text_and_leaves_trace
PASS test_methods_pending_conflict_with_existing_methods_is_recorded_not_overwritten
PASS test_methods_pending_is_a_bypass_field_and_methods_is_untouched
PASS test_methods_pending_is_json_serializable
PASS test_optimized_esp_relative_param_and_return_width
PASS test_optimized_fastcall_blind_spot_is_flagged_not_hidden
PASS test_optimized_fastcall_detected_from_edx_source_use
PASS test_optimized_stdcall_vs_cdecl_distinguished_by_ret_n
PASS test_optimized_thiscall_ecx_base_without_spill_is_detected
PASS test_optimized_thiscall_two_params_from_esp_reads
PASS test_pe_coff_reloc_lines_are_sanitized_without_semantic_change
PASS test_ruling1_disasm_must_be_raw_text
PASS test_ruling1_empty_text_is_not_silently_a_zero_arg_fn
PASS test_ruling2_genuine_fn_without_notes_still_infers
PASS test_ruling2_insufficient_evidence_is_flagged_not_defaulted
PASS test_ruling3_bare_ret_fastcall_is_still_fastcall
PASS test_ruling3_thiscall_must_not_be_misread_as_fastcall
PASS test_ruling4_bare_ret_thiscall_zero_args_vs_cdecl_unknown
PASS test_ruling4_thiscall_must_not_deduct_a_phantom_this
PASS test_ruling6_non_sret_is_not_flagged
PASS test_ruling6_sret_hidden_first_param_is_deducted
PASS test_sret_ambiguous_is_flagged_not_deducted
PASS test_sret_confirmed_including_zero_arg_form
PASS test_sret_negative_small_pointer_write_stays_grade_a
PASS test_sret_negative_void_pointer_param
PASS test_stdcall_member_this_on_stack_callee_clean
PASS test_synthetic_slots_are_skipped_not_signed
PASS test_task2_parser_raises_on_pe_coff_dir32_reloc_line
Results: 58 passed, 0 failed, 0 skipped
```

前序任务回归（同命令，逐字）：

```
$ python3 tests/test_vtable_slot_order.py        → Results: 35 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_slot_classifier.py   → Results: 34 passed, 0 failed, 0 skipped
```

> `pytest` 在本环境**恒崩**（`_pytest/assertion/rewrite.py` 的 `TypeError: required field
> "lineno" missing from alias`），与 Task 1 记录的既有环境问题一致 ⇒ 三个 vtable 测试文件
> 一律用 `python3 tests/<file>.py` 直跑（模块级 runner，与 Task 1/2 同风格）。

### 金样本自证（不是"手抄即相信"）

```
$ python3 data/status/_vtable_sig_probe_20260925/verify_fixtures.py
（重编译 rw1-rw4/opt1/opt2 + attack s1/s3/r2/e1/b1，与测试夹具逐指令比对）
夹具 39 条（函数 36 + 调用点 3）；不一致 0
```

比对口径：`(mnem, 操作数)` 序列；跳转/call 的**地址文本**归一（夹具重写过地址）。
36 个函数夹具 + 3 个调用点片段（作为所在函数的连续子序列）全部一致。

---

## 5. 实测发现（超出简报、影响后续任务）

1. **`ret N` 是栈字节数，不是参数个数**（C-1 同源缺陷）——本任务把它实现为
   `stack_slots` + `hidden_param_suspicion`；s3 `?two@SC@@UAEXHN@Z`（真值 `(int,double)`）
   `ret 0xc` 会被推成 3 参（带痕迹、B 级）。**Task 5 消费时不得把 `arity` 当精确值**，
   必须先看 `hidden_param_suspicion`。
2. **`fildl` 形态的返回宽度 f32/f64 不可分**（`rw2.cpp`：`float rf(int)` 与
   `double rd(int)` **逐字节同形**）⇒ 只能 B 级 + `fp_width_ambiguous`。
3. **`__int64` 返回只看 eax 会误判 int**（`rw3.cpp`：`mov ...,%eax; cltd`）⇒ 已按 `cltd/cdq`
   判 `i64`；否则会把 8 字节返回写成 int（调用点字节必错）。
4. **fastcall 未用实参是 /O2 的结构性盲区**（`opt2.cpp` `?fu@Os@@UAIXH@Z` 与 thiscall 0 参
   **逐字节同形**）⇒ 标 `real_param_blind_spot` + `arity_is_lower_bound`，不静默给"0 参确定"。
   真实 PAL3.exe 用 `/O2 /Ob2 /Oi /Ot /Oy` ⇒ 该形态在真实二进制里会占比不低。
5. **sret 与"指针参数 + 返回值即该指针"在 callee 字节上高度同形**
   （`rw4.cpp` `?retp@Rn2@@UAEHPAUInner@@@Z` vs `?mk@...`）：唯一稳定区别是
   store-through 的**基址寄存器个数**（真 sret = 1）。判不出时**降级不猜**（`sret_ambiguous`）。
6. **★ 发现项（Task 2 缺陷，需修但不在本任务文件范围）**：
   `tools/vtable_slot_classifier.parse_disasm_report` 在 **PE-COFF 重定位注释行**
   （objdump `-dr` 的 `6f: dir32\t$SG263` / `78: DISP32\t?log@...`）上抛
   `ValueError: invalid literal for int() with base 10: 'sg263'`（`_parse_int('sg263')`）。
   Task 2 只识别 GNU 风格 `R_386_*`（`_RELOC_LINE`），PE-COFF 的 `dir32/DISP32` 未覆盖。
   **真实 objdump 文本里凡"字符串地址压栈"的函数都有这种行** ⇒ 任何走 Task 2 解析器的
   消费者都会崩。本任务的处理：**先传原始文本**（Ruling 1），捕获 `ValueError` 后
   `sanitize_pe_relocs()` 剥该行重试，并留 `parser_error` 痕迹（不静默、不改变指令语义）。
   建议修复（属 Task 2 文件）：`_RELOC_LINE` 增加 `DISP32|dir32|off32` 分支，或
   `_att_operand` 在 `$` 后非数字时回落 `Operand('other')` 而不是让 `_parse_int` 抛异常。

---

## 6. 顾虑（影响 Task 5/6/8 与最终定性）

1. **A 级的真实占比未知**：本任务只在**独立小 TU 的 COMDAT 切片**上验证。
   PAL3.exe 是 `/O2` 且函数间内联/寄存器分配不同 ⇒ 真实二进制的
   A/B/C 分布必须先在 `PAL3.exe` 上实测（本任务未做，也不属简报范围）。
2. **`ret N`/`push` 计数不足以定参**（设计 §4.2 已自认"读集是下界"）：本任务把
   "未读槽 ⊊ ret N 槽数"一律标 `hidden_param_suspicion` ⇒ 真实二进制里**大量函数会是 B 级**。
   这是刻意保守（宁可 B 不可错），但 Task 5 的题干/棘轮口径若按"必须 A 才算通过"设计会卡死。
3. **约定推定（`cc_provisional`）**：无 ecx/edx 证据但 callee 清栈时按 `__thiscall` 推定
   （备选 `__stdcall` 成员，this 占首槽）⇒ 一律降级 B。真实二进制里 this 未被使用的
   成员函数很多，这类槽需要 IDA 定性（本任务不敢给 A）。
4. **`this` 归属依赖"vtable 槽恒为成员函数"**（`is_member=True` 默认）：若消费者把自由函数
   喂进来（非 vtable 场景），cdecl/fastcall 的 this 扣除会错 1 位 ⇒ 需显式 `is_member=False`。
5. **多返回路径/尾调用不看**：只取**最后**一个 `ret` 的 N；`jmp` 尾调用形态无 ret 即无槽数证据。
6. **ICF 降级是"一刀切"**：`icf_folded` 时把**所有**候选降到 B（含原本能判 A 的那些）。
   取舍理由：一地址多签名时"给 A 级单签名"就是 C-5 的原始缺陷；牺牲精确度换不错等价类。
7. **`methods_pending` 的 schema 是本任务首定义**（规格只说"旁路字段"）：Task 5 若需要不同
   形状，改 `build_methods_pending`/`PendingRecord.to_dict` 的**单点**即可（`iter_candidates`
   已提供只取 `(addr, candidate)` 的稳定遍历面）。
8. **未做管线集成**：本任务只交付工具 + 测试 + 探针；没有把候选接到 annotation/IDA 定性流程
   （规格 §4.2 的"第 5 步 IDA 定性"在管线里尚不存在）⇒ 候选目前只能人工/脚本消费。
9. **`pytest` 环境恒崩**（既有）⇒ 新增测试沿用模块级 runner；若 CI 只跑 pytest，本文件
   与 Task 1/2 一样**不会被收集**（需要单独补 runner 或修 pytest 环境）。

---

## 7. 证据链自检（规格 §1.2 / D-3）

* 本工具**只读**反汇编文本，**不**读 `decomp JSON`、**不**读 `data/annotations/**`、
  **不**写 IDB ⇒ 不存在 `methods → apply → Hex-Rays → 证据 → methods` 反馈环。
* CLI 显式拒绝写入 `data/annotations/**`（`main()` 里硬编码检查 + 报错退出）。
* `build_methods_pending` 用 `copy.deepcopy`：原 struct 字典在调用后**逐字未变**
  （测试 `test_methods_pending_is_a_bypass_field_and_methods_is_untouched` 断言）。

---

# 修复轮 R=1（评审：🔴 C1 + 🟡 I2/I3/I4/I5）

范围（控制器裁定）：**C1 必修** + I2（连续性判据 + 用例）+ I3/I4（各一行降级）+
I5（补 `iter_candidates` / CLI 测试）。**不做**：I6（键大小写，Task 5 分发要求）、
M8–M12（延期 minor）。禁止触碰 Task 1/2 产物 —— 本轮只改两个文件：

| 文件 | 改动 |
|---|---|
| `tools/vtable_sig_infer.py` | +112/−17 行（deref 分级、sret 连续性、`partially_parsed` 降级、多候选 cap、mangling 判据、文档同步） |
| `tests/test_vtable_sig_infer.py` | +236 行（8 条新测试 + 4 条新夹具） |

## R1.1 逐条闭合

| 发现项 | 旧行为（实测） | 新行为 | 测试 |
|---|---|---|---|
| **C1** 🔴 deref 分支逃逸 `cc_provisional` ⇒ A | 无符号时 `?wr2`/`?g`/任意 deref 形态 → `int __stdcall <n>()` arity 0 **grade A** | 无旁证 ⇒ `cc_provisional=True` + **B**；有 mangling 成员前缀 ⇒ 判开（`UAE`→thiscall/1 指针参、`UAG`→stdcall/0 参，标 `cc_from_mangling`） | `test_fix_r1_c1_deref_branch_without_symbol_is_provisional_not_grade_a`、`..._identical_bodies_two_truths_mangling_disambiguates`、`..._static_mangling_return_codes_are_not_read_as_conventions` |
| **I2** 🟡 sret 缺"连续性" | `/Od ?poff@RnA@@UAEHPAH@Z`（只写 `+0xc`，单基址，`max(covered)=15`）→ 判 sret ⇒ 误扣隐藏首参 **arity 0**（真值 1） | 要求 covered **从首址 0 起连续**到 max（≥9 字节）才判 sret | `test_fix_r1_i2_sret_requires_contiguous_store_through` |
| **I3** 🟡 `partially_parsed` 只记 note 不降级 | 丢弃 10/18 行（>50%）仍 **grade A** | `report.partially_parsed` ⇒ 至多 **B**（note 同步改成"至多 B 级"） | `test_fix_r1_i3_partially_parsed_forces_downgrade` |
| **I4** 🟡 多候选只在同体时 cap | 同地址 2 候选（体**不同**）`ambiguous=True` 但双双 **A** | `len(cands) > 1` 即 `_cap_grade(..., B)` + `multi_candidate` note | `test_fix_r1_i4_multi_candidate_different_bodies_are_capped_to_b` |
| **I5** 🟡 覆盖缺口 | `iter_candidates` / CLI 0 引用 | 补 2 条测试：遍历面契约（含裸 pending、跳过合成槽、多候选逐行）+ CLI（stdout / `--out` / 未知参数 / **拒绝写 `data/annotations`** 且不留文件） | `test_fix_r1_i5_iter_candidates_is_the_task5_traversal_face`、`..._cli_only_writes_bypass_and_refuses_truth_source` |

## R1.2 红相（先写测试，亲眼看到按预期失败）

**阶段 A**（新 API 尚未定义 ⇒ 测试文件整体 import 失败）：

```
$ python3 tests/test_vtable_sig_infer.py
ImportError: cannot import name 'FEATURE_CC_FROM_MANGLING' from 'vtable_sig_infer'
```

**阶段 B**（只加 API 占位 `convention_from_symbol → None`，**无任何修复语义**，
使各发现项的**行为红**可逐条观测）：

```
$ python3 tests/test_vtable_sig_infer.py 2>&1 | tail -1
Results: 60 passed, 6 failed, 0 skipped
```

6 条失败逐条命中预期根因（摘录）：

```
FAIL test_fix_r1_c1_deref_branch_without_symbol_is_provisional_not_grade_a:
  SignatureCandidate(..., signature='int __stdcall x()', convention='__stdcall', arity=0,
    grade='A', features={'this_on_stack','no_prologue','slot0_deref'}, cc_provisional=False)
FAIL test_fix_r1_c1_identical_bodies_two_truths_mangling_disambiguates:
  SignatureCandidate(..., symbol='?wr2@Rn6@@UAEHPAUInnerV@@@Z', signature='int __stdcall wr2()', ...)
FAIL test_fix_r1_c1_static_mangling_return_codes_are_not_read_as_conventions: AssertionError
FAIL test_fix_r1_i2_sret_requires_contiguous_store_through:
  AssertionError: frozenset({'slot0_deref','ecx_this','sret'})        ← poff 被误判 sret
FAIL test_fix_r1_i3_partially_parsed_forces_downgrade:
  SignatureCandidate(..., grade='A', notes=('partially_parsed: 丢弃 10/18 行 ...'))
FAIL test_fix_r1_i4_multi_candidate_different_bodies_are_capped_to_b:
  AssertionError: (SignatureCandidate(..., symbol='?rc@Rn@@UAEDH@Z', grade='A'),
                   SignatureCandidate(..., symbol='?ri@Rn@@UAEHH@Z', grade='A'))
```

两条 I5 测试首轮即绿 —— **I5 是覆盖缺口（不是缺陷）**，其价值是给既有
`iter_candidates` / CLI 契约上锁（首轮绿已如实记录，不当"红相"邀功）。

## R1.3 绿相 + 前序不回退

```
$ python3 tests/test_vtable_sig_infer.py | tail -1
Results: 66 passed, 0 failed, 0 skipped          # 58 前序 + 8 新

$ python3 tests/test_vtable_slot_classifier.py | tail -1
Results: 38 passed, 0 failed, 0 skipped          # Task 2 产物（未触碰）

$ python3 tests/test_vtable_slot_order.py | tail -1
Results: 35 passed, 0 failed, 0 skipped          # Task 1 产物（未触碰）
```

`pytest` 仍**恒崩**（既有环境问题，与本轮无关）：
`_pytest/assertion/rewrite.py: TypeError: required field "lineno" missing from alias`
⇒ 沿用模块级 runner（与 Task 1/2/3 一致）。

## R1.4 真机证据（本轮新探针，`/O2 /Ob2 /Oi /Ot /Oy /GR` 与 `/Od /GR`）

**C1 —— 一支探针里造出"逐字节相同的两种真值"**（这是 C1 的判据本身）：

```cpp
struct InnerV { int a; int b; int c; int d; };       // 无 vptr ⇒ b@+4, d@+0xc
struct Rn6 { virtual int wr2(InnerV* p); };          // 真值 __thiscall / 1 指针参 / int
int Rn6::wr2(InnerV* p) { p->b = 1; p->d = 3; return 0; }
struct C { int p0; int p1; int p2; virtual int __stdcall g(); };   // vptr ⇒ p0@+4, p2@+0xc
int __stdcall C::g() { this->p0 = 1; this->p2 = 3; return 0; }     // 真值 __stdcall 成员 / 0 参
```

```
$ tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include \
      /Fo/tmp/deref_form.obj /tmp/deref_form.cpp && objdump -dr /tmp/deref_form.obj
00000000 <?wr2@Rn6@@UAEHPAUInnerV@@@Z>:
   0: 8b 44 24 04           mov    0x4(%esp),%eax
   4: c7 40 04 01 00 00 00  movl   $0x1,0x4(%eax)
   b: c7 40 0c 03 00 00 00  movl   $0x3,0xc(%eax)
  12: 33 c0                 xor    %eax,%eax
  14: c2 04 00              ret    $0x4
00000000 <?g@C@@UAGHXZ>:
   （逐字节相同，与上完全一致）
```

**端到端（真机 objdump → `tools/vtable_sig_infer.py --slots … --out …`）**：

```
[vtable_sig_infer] 5 地址 / 5 候选 → /tmp/t3fix/pending_real.json
?wr2@Rn6@@UAEHPAUInnerV@@@Z    grade=A prov=False this_on_stack=False rk=i32  arity=1
   sig=int __thiscall ?wr2@Rn6@@UAEHPAUInnerV@@@Z(?)      feats=…,cc_from_mangling,slot0_deref
?g@C@@UAGHXZ                   grade=A prov=False this_on_stack=True  rk=i32  arity=0
   sig=int __stdcall ?g@C@@UAGHXZ()                        feats=…,cc_from_mangling,this_on_stack
?poff@RnA@@UAEHPAH@Z           grade=A prov=False rk=i32  arity=1  feats=…,ecx_this,slot0_deref   ← 不再是 sret
```

两者**从"同一个错答案"变成各自的真值**；同一段字节在**无** mangling 旁证时
（`test_fix_r1_c1_deref_branch_without_symbol_…`）一律 B + `cc_provisional`。

**mangling 判据独立复核**（3 支真机探针 `objdump -t` 全量符号，含**反例陷阱**）：

```
真机 mangling 判据：16 条比对，0 条不符
  OK ?v_std@M@@UAGHH@Z      got=__stdcall   ·  OK ?sf_i@N@@SAIXZ  got=None（static unsigned int()）
  OK ?priv@Q@@AAEXXZ        got=__thiscall  ·  OK ?st_std@M@@SGHH@Z got=None（static __stdcall）
```

**I2 —— 连续性判据对"带填充的真 sret"**：`struct Pad16 { char c; double d; }`（1..7 是填充）
在 `/Od` 下 MSVC 6 **连填充一起复制**（4×dword 连续写 0..0xf）⇒ 收紧后仍判 sret；
同 TU 的 `?pwrite@Rn11@@UAEHPAUPad16@@@Z`（`q->d = 2.5` 只写 `+0x8/+0xc`，单基址、`max=15`）
⇒ 旧实现误判 sret，现正确给 `int __thiscall (?)`/arity 1：

```
?mkp@Rn11@@UAE?AUPad16@@XZ   -> <struct> __thiscall …() grade=A arity=0 sret=True   （真值 sret/0 参）
?mkq@Rn11@@UAE?AUPad12@@H@Z  -> <struct> __thiscall …(?) grade=A arity=1 sret=True   （真值 sret/1 参）
?pwrite@Rn11@@UAEHPAUPad16@@@Z -> int __thiscall …(?) grade=A arity=1 sret=False      （真值 1 指针参）
```

## R1.5 本轮新发现（不在裁定范围，交控制器裁定）

1. **`/O2` 真 sret 的 store-through 会被"寄存器复制"截断**（新证据，未修）：
   `/O2 ?mk@Rn8@@UAE?AUInner@@H@Z` 是 `mov 0x4(%esp),%eax … mov %eax,%edi`，
   后续写出经 **edi**（`reg_slot` 不跨 `mov reg,reg` 传播）⇒ `store_through` 为空 ⇒
   既判不出 sret，也拿不到返回宽度：现输出 `? __thiscall (?,?)`、**grade B**、`arity=2`
   （真值 `(int)` + 隐藏 sret）。**它是 B 级（不误给 A）**，故不构成新的 🔴，但
   `/O2` 真实二进制里 sret 槽的 arity 会**整体多 1** ⇒ 建议下一轮加"`mov reg,reg` 传播
   `reg_slot`"（约 3 行，风险点：`store_through` 语义面变宽，须重跑全部 sret 夹具）。
2. **本轮两支新探针源未入库**：`/tmp/deref_form.cpp`（C1）与 `/tmp/pad_sret.cpp`（I2 阴性对照）
   的**完整源码 + 编译命令**已逐字写进测试文件注释，但 `.cpp` 不在仓里 ⇒
   `verify_fixtures.py` 的 `PROBES/FIXTURES` 表**不含**本轮夹具（新夹具尚未自证）。
   建议按 I7 判例由控制器把探针入库 + 接进 `verify_fixtures.py`
   （本轮 `git add` 严格限定两个文件，未越权）。

## R1.6 顾虑

1. **mangling 是"元数据旁证"，不是指令字节**：本轮只在 deref 形态（字节不可判）用它判开，
   并加了**清栈形态自洽**校验（`UAE` 要求 `ret N`、`UAA` 要求裸 `ret`，否则退回推定 B）。
   若上游符号本身错（误归属/PDB 猜测），该槽会得到"有旁证"的错约定；已用
   `cc_from_mangling` feature 留痕，Task 5 可据此单列复核。
2. **`convention_from_symbol` 的覆盖面是保守的**：模板类（类名含 `@`）、自由函数、
   析构、static 一律 `None` ⇒ 这些槽仍是 B 级（宁可 B 不可错）。
3. **B 级占比进一步上升**：C1/I3/I4 三处都是"降级"⇒ 真实二进制里 A 级占比会低于
   Task 3 首轮的估计（Task 5 棘轮口径必须接受 B/C 带证据，这一点未变）。
4. **I6（methods 键 32 个小写）仍未处理**：按裁定属 Task 5 分发要求（`_addr_key` 已归一
   `0x%08X`，但**读**已存在 `methods` 键做冲突对账时未做大小写归一）。
5. **M8–M12 仍延期**（README 算术错 / 红相不可验证 / `--struct` 语义坏 / CLI 拒写前缀
   误拒 / 死分支）—— 其中 `--struct`（M11）会让 CLI 把 struct JSON 当 slots 读，
   本轮**没有**为它补测试（避免把既定缺陷固化成契约）。

---

# 修复轮 R=2（评审：🔴 sret 安全网不可达 + 3 项收尾）

范围（控制器裁定）：① 恢复 `sret_ambiguous` 安全网（必修）② 测试卫生（残留假失败）
③ 新夹具接入 `verify_fixtures.py` ④ 3 处手抄字节。禁止触碰 Task 1/2 产物与
`tools/vtable_slot_classifier.py` / `tools/vtable_slot_order.py`；不读 decomp JSON。
本轮只改 3 个文件：

| 文件 | 改动 |
|---|---|
| `tools/vtable_sig_infer.py` | +16/−4 行（sret 判定块 `elif` 安全网 + Ruling 6 文档同步） |
| `tests/test_vtable_sig_infer.py` | +121/−15 行（1 新真机夹具 + 2 新测试 + 残留免疫 helper + 3 处字节修正） |
| `data/status/_vtable_sig_probe_20260925/verify_fixtures.py` | +9 行（3 探针入 `PROBES`，4 夹具入 `FIXTURES`） |

## R2.1 逐条闭合

| 发现项 | 旧行为（实测原文） | 新行为 | 测试 |
|---|---|---|---|
| **1** 🔴 `sret_ambiguous` 不可达 | 多基址 + >8B + **不连续** ⇒ `int __thiscall mwp(?)` / **A** / `{ecx_this, slot0_deref, ambiguous_param_class}` —— **无痕迹**（R=1 前同输入 = B + `{sret_ambiguous, hidden_param_suspicion}`） | `elif len(bases) > 1 and max(covered) >= 8: sret_ambiguous = True` ⇒ 不扣除但留痕、降级 **B** | `test_fix_r2_sret_ambiguous_survives_non_contiguous_multi_base`（含真 sret 阳性对照 + `?poff` 仍 A 阴性对照） |
| **2** 🟡 测试卫生 | 残留 `data/annotations/__r1_cli_must_never_write.json` ⇒ `assert not forbidden.exists()` **假失败**（65 passed / 1 failed） | 抽出 `_cli_refuses_truth_source_write`：清理放在 CLI **调用前**（放在断言前是空断言）；I5 改走该 helper | `test_fix_r2_truth_source_refusal_is_immune_to_residue`（主动制造残留） |
| **3** 收尾 夹具未自证 | `verify_fixtures.py` 表 39 条，不含本轮 4 新夹具 ⇒ "不一致 0" 不覆盖新金样本 | `PROBES` += `deref_form`(/O2…/GR) / `rw5`(/Od /GR) / `rw6`(/Od /GR)；`FIXTURES` += `C1_R1_DEREF_SAME_BYTES` / `C1_R1_POFF_GAP` / `C1_R1_PAD_SRET` / `C1_R1_PWRITE_NOT_SRET` ⇒ **43 条** | `python3 …/verify_fixtures.py`（真机重编译逐指令比对） |
| **4** 小误 3 处手抄字节 | `8b e5` 抄成 `mov %esp,%ebp`（objdump 实为 `mov %ebp,%esp`）⇒ 对**工具语义惰性**，但对 `verify_fixtures` 的 `(mnem,操作数)` 比对**不惰性**（见 R2.5-2 实测） | 3 处改为 `mov %ebp,%esp`（`C1_R1_POFF_GAP:14` / `PAD_SRET:38` / `PWRITE_NOT_SRET:1a`） | 既有两个 R=1 测试 + 新接入的 `verify_fixtures` |

## R2.2 红相（先写测试，亲眼看到按预期失败）

**① 修复项 1 —— 行为红**（只加夹具与测试，未动 `tools/`）：

```
$ python3 tests/test_vtable_sig_infer.py 2>&1 | grep -E "FAIL|Results"
  FAIL test_fix_r2_sret_ambiguous_survives_non_contiguous_multi_base: AssertionError: frozenset({'slot0_deref', 'ambiguous_param_class', 'ecx_this'})
  PASS test_fix_r2_truth_source_refusal_is_immune_to_residue
Results: 67 passed, 1 failed, 0 skipped
```

同输入在 **R=1 前 / R=1 后** 两版工具上的原文对照（新夹具 `?mwp@Rn7@@UAEHPAUInnerV@@@Z`）：

```
PRE-R1 (d06ede038^) : int __thiscall mwp(?) | B | ['ambiguous_param_class','ecx_this','hidden_param_suspicion','slot0_deref','sret_ambiguous'] | hidden=True
R=1   (HEAD)        : int __thiscall mwp(?) | A | ['ambiguous_param_class','ecx_this','slot0_deref']                                   ← 痕迹消失
```

⇒ 与评审判断一致：**B + 痕迹 → A + 无痕迹**（A 级契约 = 约定/个数/返回宽度全确定且无隐藏参数嫌疑）。

**② 修复项 2 —— 残留假失败，用 R=1 的测试文件逐字复现**（临时文件，随即删除）：

```
$ : > data/annotations/__r1_cli_must_never_write.json          # 制造残留（0 字节）
$ git show HEAD:tests/test_vtable_sig_infer.py > tests/_r2_red_old_test.py
$ python3 tests/_r2_red_old_test.py 2>&1 | grep -E "FAIL|Results"
  FAIL test_fix_r1_i5_cli_only_writes_bypass_and_refuses_truth_source: AssertionError: /home/peng/workspace/PAL3Decomp/data/annotations/__r1_cli_must_never_write.json
Results: 65 passed, 1 failed, 0 skipped
```

## R2.3 绿相（**残留文件仍在**的情况下）

```
$ ls -la data/annotations/__r1_cli_must_never_write.json
-rw-rw-r-- 1 peng peng 0  9月 24 22:31 data/annotations/__r1_cli_must_never_write.json

$ python3 tests/test_vtable_sig_infer.py       | tail -1
Results: 68 passed, 0 failed, 0 skipped         # 66 前序 + 2 新（R=2）
$ python3 tests/test_vtable_slot_classifier.py | tail -1
Results: 38 passed, 0 failed, 0 skipped         # Task 2 产物（未触碰）
$ python3 tests/test_vtable_slot_order.py      | tail -1
Results: 35 passed, 0 failed, 0 skipped         # Task 1 产物（未触碰）
```

同一残留场景 R=1 是 65 passed/1 failed ⇒ 假失败已消除（清理在调用前，断言语义反而**强于**原文：
跑完 CLI 后文件存在就只能归因于 CLI 真写了）。

**变异检验**（临时删掉 helper 里两行清理 ⇒ 新测试必须红；随即从备份恢复）：

```
$ python3 tests/test_vtable_sig_infer.py 2>&1 | grep -E "FAIL|Results"
  FAIL test_fix_r2_truth_source_refusal_is_immune_to_residue: AssertionError: /home/peng/workspace/PAL3Decomp/data/annotations/__r1_cli_must_never_write.json
Results: 67 passed, 1 failed, 0 skipped
```

`pytest` 仍恒崩（既有环境问题，与本轮无关）⇒ 沿用模块级 runner。

## R2.4 金样本自证（`verify_fixtures.py`，真机重编译逐指令比对）

```
$ python3 data/status/_vtable_sig_probe_20260925/verify_fixtures.py 2>&1 \
      | grep -E "C1_R1_|夹具"
  OK        C1_R1_DEREF_SAME_BYTES ?wr2@Rn6@@UAEHPAUInnerV@@@Z
  OK        C1_R1_PAD_SRET ?mkp@Rn11@@UAE?AUPad16@@XZ
  OK        C1_R1_POFF_GAP ?poff@RnA@@UAEHPAH@Z
  OK        C1_R1_PWRITE_NOT_SRET ?pwrite@Rn11@@UAEHPAUPad16@@@Z
夹具 43 条（函数 40 + 调用点 3）；不一致 0
```

基线（本轮改动前，同命令）：`夹具 39 条（函数 36 + 调用点 3）；不一致 0` ⇒ **39 → 43，不一致仍 0**。

**R=2 新夹具的出处（真机，非手抄）** —— 探针源与命令逐字写进测试注释：

```
$ tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw7.obj /tmp/rw7.cpp
$ objdump -dr /tmp/rw7.obj
00000000 <?mwp@Rn7@@UAEHPAUInnerV@@@Z>:
   0: 55                    push   %ebp
   1: 8b ec                 mov    %esp,%ebp
   3: 51                    push   %ecx
   4: 89 4d fc              mov    %ecx,-0x4(%ebp)
   7: 8b 45 08              mov    0x8(%ebp),%eax
   a: c7 00 01 00 00 00     movl   $0x1,(%eax)
  10: 8b 4d 08              mov    0x8(%ebp),%ecx
  13: c7 41 08 02 00 00 00  movl   $0x2,0x8(%ecx)
  1a: 8b 45 08              mov    0x8(%ebp),%eax
  1d: 8b e5                 mov    %ebp,%esp
  1f: 5d                    pop    %ebp
  20: c2 04 00              ret    $0x4
```

两个基址（eax/ecx），`covered = {0..3} ∪ {8..0xb}`（`max=11 ≥ 8` 但**不连续**）——
`C1_R2_MULTI_BASE_GAP` 即上列**逐字**输出。扫描层判决（修复后）：

```
_scan(C1_R2_MULTI_BASE_GAP) ⇒ sret_slot=None  sret_ambiguous=True
                              features=['ecx_this', 'slot0_deref', 'sret_ambiguous']   # 不扣除，但留痕
```

## R2.5 本轮实测发现（超出简报）

1. **`deref_form.cpp` 的两种真值是两个独立 COMDAT 段**（同一地址 `0x0`，段体逐字相同）：
   `objdump -dr` 对 `?wr2@Rn6@@UAEHPAUInnerV@@@Z` 与 `?g@C@@UAGHXZ` 各打一个标签、各一段，
   两段指令完全相同（`8b 44 24 04 / c7 40 04 01… / c7 40 0c 03… / 33 c0 / c2 04 00`）。
   ⇒ C1 的"逐字节相同"由真机证实；`FIXTURES` 表"一夹具一符号"只列了 `?wr2` 标签（本轮保持 4 条），
   若要给 `?g` 单独上表，只需在测试文件加一个别名常量（未做，避免越权扩大改动面）。
   另注：夹具文本**不含**真实体尾部的 9 个 `nop`，比对用前缀判据（`g[:len(want)] == want`）故仍 OK。
2. **修复项 4 不是"纯卫生"**（实测，非推理）：把 HEAD 版本的夹具文本与新编译的 `rw5.obj`/`rw6.obj` 比对：

   ```
   C1_R1_POFF_GAP         HEAD(手抄 mov %esp,%ebp) 对齐=False | 修正为 mov %ebp,%esp 后对齐=True
   C1_R1_PAD_SRET         HEAD(手抄 mov %esp,%ebp) 对齐=False | 修正为 mov %ebp,%esp 后对齐=True
   C1_R1_PWRITE_NOT_SRET  HEAD(手抄 mov %esp,%ebp) 对齐=False | 修正为 mov %ebp,%esp 后对齐=True
   ```

   ⇒ 若不同时修这 3 处，修复项 3 一接入就是 **3 条 MISMATCH**（两项耦合，必须同轮落地）。
   而**工具语义**确为惰性（同一夹具改前/改后 `(signature, grade, arity, return_kind, features)` 全等）：

   ```
   C1_R1_POFF_GAP         语义惰性=True | int __thiscall x(?) / A / arity=1 / ['ambiguous_param_class','ecx_this','slot0_deref']
   C1_R1_PAD_SRET         语义惰性=True | <struct> __thiscall x() / A / arity=0 / ['ecx_this','slot0_deref','sret']
   C1_R1_PWRITE_NOT_SRET  语义惰性=True | int __thiscall x(?) / A / arity=1 / ['ambiguous_param_class','ecx_this','slot0_deref']
   ```
3. **`?poff` 仍 A**（阴性对照已写进新测试）：单基址 + 不连续 ⇒ 不进新 `elif`，
   `(grade, arity) = (A, 1)`、无 `sret_ambiguous` / 无 `hidden_param_suspicion`。

## R2.6 顾虑

1. **新夹具 `C1_R2_MULTI_BASE_GAP` 未进 `verify_fixtures.py`**：其探针源 `/tmp/rw7.cpp` 未入库
   （本轮 `git add` 严格限定 3 个文件），出处只有测试注释里的源码 + 编译命令。
   若要像 R=1 探针那样自证，需由控制器裁定把 `rw7.cpp` 入库并加一行 `FIXTURES`
   （否则"不一致 0"对这条新金样本仍不覆盖）。
2. **新 `elif` 依赖"`bases` 与 `covered` 同源"不变量**：`len(bases) > 1` ⇒ `covered` 必非空
   （`store_through` 每个键至少写入 1 字节）⇒ `max(covered)` 不会空集报错。本轮**照抄评审的
   1 行**未加 `covered and` 守卫；若日后重构 `store_through` 的构造，须复查该不变量。
3. **B 级内部仍需靠 feature 名区分**：`sret_ambiguous`（返回可能 >8B 结构）与
   `hidden_param_suspicion`（未读槽 / 槽数不匹配）都并入 `hidden_param_suspicion` 字段 ⇒
   Task 5 的棘轮必须读 `features`，不能只看 `grade`/`hidden_param_suspicion` 布尔。
4. **前序 R1.5-1 仍未修**：`/O2` 真 sret 被 `mov reg,reg` 截断 `reg_slot` 传播 ⇒ arity 整体多 1
   （仍是 B 级不误给 A）。本轮未触碰。
5. **`ret N`/未读槽/寄存器盲区三条降级路径不变** ⇒ 真实 PAL3.exe 上 B 级占比仍会偏高，
   Task 5 的通过口径必须接受"B + 证据"。
