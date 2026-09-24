# Task 2 报告：vtable 合成槽分类器（二进制可观测形态）

- **状态**: DONE
- **交付**: `tools/vtable_slot_classifier.py` + `tests/test_vtable_slot_classifier.py`（TDD：先测试红 → 实现绿 → 重构）
- **测试**: `python3 tests/test_vtable_slot_classifier.py` ⇒ **27 passed, 0 failed, 0 skipped**
- **提交**: （见文末「提交」行）——本目录 `.superpowers/sdd/` 被本地 `.gitignore` 排除，报告不在提交内

---

## 1. 词表与 API（供 Task 1 槽序 / Task 5 声明校验对接）

6 种 kind（简报词表）：`fn`｜`deleting_dtor`｜`adjustor_static`｜`adjustor_vbase`｜`purecall`｜`composite`。

```python
from vtable_slot_classifier import SlotEvidence, classify_slot, parse_disasm

ev  = SlotEvidence(symbols=('??_GV@@UAEPAXI@Z', '??_EV@@UAEPAXI@Z'),   # 同址符号（含弱别名）
                   signature='void*(unsigned)',                        # 可空 = 证据缺失
                   instructions=parse_disasm(objdump_text),            # 原始指令字节反汇编
                   is_external=False, external_symbol='', addr='0x401234')
res = classify_slot(ev)      # SlotClassification(kind, features, notes)
res.kind                     # 'deleting_dtor'
res.features                 # 命中特征集 {'deleting_dtor'}
res.notes                    # 证据/排除痕迹（审计、Task 5 诊断）
res.needs_manual_review      # composite ⇒ True（需 IDA 人工定性）
res.slot_order_kind          # 喂 Task 1 SlotEntry.kind（'fn'→'func'，其余原样）
```

辅助件：`parse_disasm`（objdump AT&T / ndisasm Intel / IDA 裸文本三种逐字反汇编）·
`normalize_signature` / `is_deleting_dtor_signature`（签名书写归一）· `normalize_kind` / `slot_order_kind`
（词面互认，见顾虑 1）。

## 2. 判据精确表述（特征 → kind）

**证据只来自二进制可观测形态**：原始指令字节的反汇编（objdump/ndisasm/IDA 文本）、地址特征
（同址符号 / 外部符号 / 跳转目标形态）。**不使用 decomp JSON，不解析 mangling**。

| kind | 特征（命中即入 `features`） | 实测金样本 |
|---|---|---|
| `fn` | 零特征（默认） | `?h@D@@UAEHXZ`（abi #2）· `?v@DV@@UAEHXZ`（abi #4 反例） |
| `deleting_dtor` | ① 与 `??_G` 共享地址（同址 `??_G`/`??_E` 弱别名）＋ 签名 `void*(unsigned)`（或缺失⇒"未确认"）；② 无符号证据时的形态推断（顾虑 2） | `??_GV@@UAEPAXI@Z`（abi #7） |
| `adjustor_static` | 调整链全为 `add/sub imm,%ecx`（**仅 ecx 操作数**）+ 尾部**直接** jmp | `?ff@D3@@W7AEHXZ`（abi #3，字节 `83 e9 08 e9 ...`） |
| `adjustor_vbase` | 动态 delta：`sub -N(%ecx),%ecx` 直接形 **或** vbtable 间接形（`mov r,mem(%ecx)` → `sub mem(%r),%ecx`）+ 尾 jmp | `?o@D@@$4PPPPPPPM@A@AEXXZ`（abi #5） |
| `purecall` | 槽指向 CRT stub / 外部符号 `__purecall`（名字归一比对，不解析 mangling） | `??_7Q2@@6B@[0] = __purecall`（abi #6，coff_vtable 提取） |
| `composite` | **≥2 个特征同时命中**（混合链 / deleting_dtor × adjustor 混合） | `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z`（attack B-1） |

**`adjustor_*` 的强制排除项**（简报明列，命中即"排除"痕迹 + 不判 adjustor）：

| 排除项 | 判据 |
|---|---|
| import thunk（`j_*` 家族） | 同址符号属 `j_*` / `__imp_*` / `_imp__*` |
| import thunk（间接跳转体） | 尾部 jmp 为**间接**（`jmp *addr` / `jmp dword ptr ds:…`） |
| 增量链接 thunk | `mov %edi,%edi; push $t; jmp` 一类（跳转前有栈/帧操作） |
| 参数转发包装器 | 跳转前动栈（`esp`/`ebp` 操作数）或存在非 this 调整指令 |

**adjustor 形态的强判据**：整函数体 = `[调整链] + 尾部直接 jmp`，链内每条都必须是
this 调整（静态 `add/sub imm,%ecx` / 动态 `sub mem,%ecx` / vbtable 间接两指令对）。
⇒ 只要跳转前动了栈、或有别的指令（哪怕也碰 ecx），就不是 adjustor。
反例钉死（防止假阳）：`?v@DV@@UAEHXZ` 本体内有 `mov -0x4(%ecx),%eax`（vbtable 相对读）
但**无尾 jmp** ⇒ `fn`，不得判 adjustor（测试 `test_fn_vbtable_read_in_body_is_not_an_adjustor`）。

## 3. 金样本（全部真机实测，逐字反汇编进测试夹具）

方法可信度：本任务用 README 复现命令在真机 MSVC 6.0 SP0（cl 12.00.8168，`tools/wine_cl.sh`）
重新编译 `vt2.cpp` / `vt3.cpp` / `q2a.cpp` / `c2.cpp`，COMDAT 原始字节经 `tools/coff_vtable.py`
的 `parse_obj` 取出后用 objdump/ndisasm 反汇编，**逐字与两个 README 的记载一致**（含 B-1 的 11 字节）。
夹具即这些逐字输出（测试内联硬编码，不依赖可删除的草稿目录）。

| 测试 | 金样本 | 实测证据 |
|---|---|---|
| `test_fn_plain_virtual_body_is_default_kind` | `?h@D@@UAEHXZ` | abi #2（`mov 0x8(%ecx),%eax; ret`） |
| `test_fn_vbtable_read_in_body_is_not_an_adjustor` | `?v@DV@@UAEHXZ` | abi #4（`mov -0x4(%ecx),%eax; ret`）反例 |
| `test_deleting_dtor_shared_addr_and_signature` | `??_GV@@UAEPAXI@Z` | abi #7：`??_G` + `??_E` 弱别名同址（COFF `scl 2`/`scl 105`）、46 字节全本体、签名 `void*(unsigned)` |
| `test_deleting_dtor_signature_text_variants_all_match` | 6 形正例 + 5 形反例 | 签名书写归一（含 IDA 显式 this 形） |
| `test_deleting_dtor_symbol_without_signature_is_unconfirmed_but_hit` | 同上 | 签名缺失 ⇒ 判但留「未确认」 |
| `test_deleting_dtor_symbol_with_contradicting_signature_is_rejected` | 同上 | 签名 `void()` ⇒ 不判 + 「矛盾」 |
| `test_deleting_dtor_shape_inferred_without_symbols` | `??_GV` 形态 | 扩展判据（顾虑 2） |
| `test_shape_inference_requires_deleting_dtor_skeleton` | 合成反例 | 1 个 call / 无释放骨架 ⇒ 不推断 |
| `test_adjustor_static_sub_imm_jmp_thunk` | `?ff@D3@@W7AEHXZ` | abi #3（vt3 实测 `83 e9 08 e9 00 00 00 00`） |
| `test_adjustor_static_add_imm_jmp_form` | `add $0xfffffff8,%ecx; jmp` | 负 delta 的 add 发射形态 |
| `test_adjustor_vbase_dynamic_delta_jmp` | `?o@D@@$4PPPPPPPM@A@AEXXZ` | abi #5（c2 实测 `2b 49 fc e9 ...`） |
| `test_adjustor_vbase_same_conclusion_under_intel_syntax` | 同上 × ndisasm/IDA 两语法 | 语法无关性（attack B-1 以 Intel 形态记载） |
| `test_adjustor_vbase_vbtable_indirect_delta` | `mov -0x4(%ecx),%eax; sub 0x4(%eax),%ecx; jmp` | vbtable 间接调整形 |
| `test_purecall_external_crt_stub` / `..._name_variants_recognised` | `??_7Q2@@6B@[0] = __purecall` | abi #6（q2a.obj 实测） |
| `test_composite_b1_mixed_slot_needs_manual_adjudication` | `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z` | attack **B-1**：`sub -0x4(%ecx),%ecx; sub $0x10,%ecx; jmp`（11 字节）= 动态 vbase × 常量 delta × deleting dtor ⇒ 三特征 |
| `test_composite_mixed_thunk_without_dtor_symbol` | 同形态无 `??_E` | 混合调整链仍 ⇒ composite |
| `test_import_thunk_symbol_family_excluded…` / `test_indirect_jmp…` / `test_incremental_linking_thunk…` / `test_parameter_forwarding_wrapper…` | 4 个排除用例 | 简报明列的 3 类排除 |
| `test_kind_vocabulary_and_task1_slot_order_alias` / `test_unknown_kind_rejected` | 词表 | 与 Task 1 `SlotEntry.kind` 互认（顾虑 1） |
| `test_notes_record_which_evidence_matched` | B-1 | 证据痕迹可审计 |
| `test_golden_matrix_all_six_kinds` | 6 kind 总表 | 回归总控（6 种各 ≥1 实测例） |
| `test_parse_disasm_*` × 2 | 逐字反汇编解析 | 含 listing 头剔除（端到端核对发现的缺陷，见 §5） |

**端到端核对**（非测试，报告证据）：对真机 4 个 .obj 的**全部** COMDAT 体走
`parse_obj → objdump -D → parse_disasm → classify_slot`，与 README 定性逐条相符：

```
??_GV@@UAEPAXI@Z / ??_GA / ??_GBx / ??_GD        -> deleting_dtor   ['deleting_dtor']
??_ED@@$4PPPPPPPM@BA@AEPAXI@Z                    -> composite       ['adjustor_static','adjustor_vbase','deleting_dtor']
?o@D@@$4PPPPPPPM@A@AEXXZ                         -> adjustor_vbase  ['adjustor_vbase']
?ff@D3@@W7AEHXZ                                  -> adjustor_static ['adjustor_static']
?h@D@@UAEHXZ / ?v@DV@@UAEHXZ / ?ff@D3@@UAEHXZ   -> fn              []
??_7Q2@@6B@[0]=__purecall                        -> purecall        ['__purecall', ...]
```

## 4. TDD 记录（红 → 绿 → 重构）

1. **红 1**：只写 `tests/test_vtable_slot_classifier.py`（26 测）⇒ `ModuleNotFoundError`（功能缺失）。
2. **红 2**：落 API 骨架（数据模型 + 词表，`parse_disasm`/`normalize_signature`/`classify_slot` 抛
   `NotImplementedError`）⇒ 24 测逐条以「功能缺失」失败（2 条词表测在骨架期即绿——它们对应的
   代码就是词表本身；红 1 阶段该 2 测同样失败过）。
3. **绿**：实现解析 + 判据 ⇒ 24/26 绿，2 红都是**真失败**：AT&T 操作数规范序只对 `add/sub` 做了交换，
   导致 `mov -0x4(%ecx),%eax` 的 dst/src 颠倒（vbtable 间接链不认）与 `and $0x1,%eax` 同因不认 ⇒ 修解析。
4. **绿**：26/26。
5. **缺陷修复（TDD）**：端到端核对真机 .obj 时发现 objdump 节头行（`Disassembly of section .data:`）
   被当指令解析、打断调整链 ⇒ **先写复现测试** `test_parse_disasm_skips_listing_headers`（红）⇒ 修 ⇒ 27/27 绿。
6. **变异检验**（证明测试有判别力，非事后补测）：① 签名判据退化成字面相等 ⇒ 被杀 ✓；
   ② 去掉 import thunk 排除 ⇒ 被杀 ✓。
7. **回归**：Task 1 `tests/test_vtable_slot_order.py` 35/35 仍绿（未触碰）。

## 5. 设计决策

| # | 决策 | 依据 |
|---|---|---|
| 1 | kind 词面以简报为准（`fn`），同时提供 `slot_order_kind`/`normalize_kind` 与 Task 1 的 `func` 互认 | 简报词表 vs Task 1 实测代码（顾虑 1） |
| 2 | `composite` = 命中特征数 ≥2，`needs_manual_review` 恒 True；**不自动挑一个 kind** | attack **B-1**：混合槽"无 kind 可归"，编造归类会把 thunk 性质丢掉 |
| 3 | deleting_dtor 证据优先级：符号（主）→ 签名缺失判但"未确认" → 签名矛盾不判 → 形态推断（仅无符号时） | 简报特征 + 真实二进制符号缺失现实（顾虑 2/3） |
| 4 | adjustor 判据 = **整形态**（调整链 + 尾部直接 jmp），不是"序言前几条像" | abi #4 反例：本体内 vbtable 读不是 adjustor；序言松判会大面积假阳 |
| 5 | 三种反汇编语法同结论（objdump AT&T / ndisasm Intel / IDA 文本），操作数统一规范成 `(dst, src)` | 证据来自原始字节，不因反汇编器而变；IDA 侧是 Intel 语法 |
| 6 | 排除项独立成闸（import 家族符号 / 间接尾跳 / 栈操作），并留"排除"痕迹 | 简报明列"必须排除"；痕迹供 Task 5 诊断，避免静默回落 |
| 7 | 逐字反汇编行可直接喂（含 objdump listing 头自动剔除） | 证据链 = 原始字节 → 反汇编文本 → 判据，测试夹具即逐字输出 |

## 6. 顾虑 / 待上层裁定

1. **词面冲突（建议统一）**：简报说 Task 1 `SlotEntry.kind` 支持 `fn`，但 Task 1 实测代码是
   `KIND_FUNC = 'func'`（`tools/vtable_slot_order.py` 词表段）⇒ 分类器以简报词面 `fn` 产出，
   经 `slot_order_kind()` 转 `func` 喂 Task 1（`SYNTHETIC_KINDS` 其余词面两边一致）。**建议上层二选一
   统一**：把 Task 1 的 `KIND_FUNC` 改 `fn`，或让 Task 2 直接产出 `func`。现在两头都能对接，但词面
   不统一会让 Task 5/6 的字符串比较出错。
2. **deleting_dtor 形态推断 = 超出简报特征表的扩展（请裁定是否保留）**：简报特征"与 `??_G` 共享地址"
   依赖符号可见，而"真实二进制 531 条函数名仅 4 条 mangled" ⇒ PAL3.exe 里 `??_G`/`??_E` 名很可能**不可见**，
   那时按表实现会把删除器全判成 `fn`（静默误判）。故加了一支**只在无符号证据时生效**的形态推断
   （签名 `void*(unsigned)` + `and r,1 → test r,r → 条件跳过含 call 的释放块` + 全体 ≥2 个 call；
   真机 4 个 deleting dtor 同骨架），结论留「形态推断」痕迹。**不改变任何有符号证据样本的结论**；
   若不认可，删 `classify_slot` 中该分支即可，测试同步删 2 条。
3. **签名证据缺失/矛盾的语义**（同上需认可）：`??_G` 同址 + 签名缺失 ⇒ 仍判 `deleting_dtor` 但「未确认」；
   签名**已知且矛盾** ⇒ 不判（「矛盾」痕迹）。理由：IDA 未标注期签名常缺失，回落 `fn` 是最危险的静默误判。
4. **composite 只能标记不能定性**：B-1 三特征槽判 `composite` + `needs_manual_review`，最终归类必须 IDA 人工；
   且 attack **B-4** 指出动态 delta 无法归一成 `(target, this_delta)` 二元组 ⇒ Task 6 对比项至少要
   `(target, kind=dynamic, const)`，不能把 `sub ecx,[ecx-4]; sub ecx,0x10` 归一成 `0x10`。
5. **排除项保守方向**：「参数转发包装器」与真 thunk 的区分靠"仅 ecx 操作数 + 整形调整链"强判
   （跳转前动栈/有多余指令即否）。极端形态的真 adjustor 若带冗余指令会被误否——方向保守
   （宁判 `fn`+痕迹，不假阳 `adjustor`），但确实可能漏判。
6. **本环境 pytest 损坏（与本任务无关）**：`python3 -m pytest --version` 自身崩——`pytest` 从
   `~/workspace/aide/benchmarks/swe_bench_lite_100/worktrees/pytest-dev__pytest-7432/src` 的陈旧开发树加载，
   Python 3.10 断言重写崩在 `TypeError: required field "lineno" missing from alias`；对 Task 1 既有
   测试同样崩 ⇒ 环境问题。测试以文件内独立运行器验证（`python3 tests/test_vtable_slot_classifier.py`）。
   建议另行修环境（PATH/PYTHONPATH 清理），不在本任务范围。
7. **`??_E` 前缀的语义确认**：B-1 thunk 自身符号以 `??_E` 开头 ⇒ 命中 deleting_dtor 特征——与 attack
   README 的原判断（"`??_E` 命中 deleting_dtor ⇒ 把 thunk 性质丢了"）一致；因其调整链同时命中 ⇒
   最终 `composite`，thunk 性质**不丢**。若上层认为 thunk 自身符号不应触发 deleting_dtor 特征，
   只需把符号判据收窄到「同址**另一条**符号是 `??_G`」，一行改动。

## 附录：复现

```sh
cd /home/peng/workspace/PAL3Decomp
# 金样本编译（真机 MSVC6 SP0）
tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/t2probe/vt2.obj data/status/_vtable_abi_probe_20260925/vt2.cpp
tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/t2probe/vt3.obj data/status/_vtable_abi_probe_20260925/vt3.cpp
tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/t2probe/q2a.obj data/status/_vtable_abi_probe_20260925/q2a.cpp
tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/t2probe/c2.obj  data/status/_vtable_attack_cases_20260925/c2.cpp
# 反汇编（夹具来源）：COMDAT 原始字节（tools/coff_vtable.py parse_obj）→ objdump -D -b binary -m i386
python3 tests/test_vtable_slot_classifier.py      # 27 passed
```

---

# 追加修复记录：解析器静默失败缺陷（2026-09-24）

> 本附录由后续修复会话**追加**，正文（首版交付）**未改动**；正文的 27 测结论仍然成立。
> 修复后：`python3 tests/test_vtable_slot_classifier.py` ⇒ **34 passed**（27 原测 + 7 新测）。

## F1. 缺陷一句话

`classify_slot()` 的反汇编解析器对不认识的行**静默丢弃**（或解析成伪指令），使真 adjustor thunk
的尾 `jmp` 不再位于末位 / 调整链断裂 ⇒ 误判成**零 notes 的静默 `fn`**（真 thunk 就这样消失）。
三例实测 + 一条"证据不足"缺口：

| # | 输入形态（逐字） | HEAD 行为 | 修复后 |
|---|---|---|---|
| 1 | `  3: R_386_PC32  ?o@D@@$4PPPPPPPM@A@AEXXZ`（`objdump -dr` 重定位注释行） | 解析成伪指令 `r_386_pc32` ⇒ 抢占末位 ⇒ `fn`（**零 notes**） | 跳过 ⇒ `adjustor_vbase` |
| 2 | `CODE:00401000 sub ecx,[ecx-4]` / `00401000  sub ecx,[ecx-4]`（IDA 地址列前缀） | `code` 伪指令 / 整行丢弃 ⇒ `fn`（**零 notes**） | 剥前缀 ⇒ `adjustor_vbase` |
| 3 | `sub ecx,[ecx-4]  ; adjust this`（IDA 行尾注释） | `;` 未剥 ⇒ 操作数 `other` ⇒ 调整链断 ⇒ `fn` | 剥注释 ⇒ `adjustor_vbase` |
| 4 | 非空文本但解析不出任何指令 | **静默** `fn` + 零 notes | 留 `insufficient_evidence` 痕迹 |

**覆盖测试文件**：`tests/test_vtable_slot_classifier.py`（新增 §9「解析器健壮性」，**+7 测**，27 → 34）
**修复实现文件**：`tools/vtable_slot_classifier.py`

| 新增测试 | 钉死的缺陷 |
|---|---|
| `test_objdump_reloc_annotation_lines_are_skipped` | 例 1（`R_386_*` + `R_IA64_*` 两家族、带 `offset:` 前缀） |
| `test_reloc_and_structural_lines_are_not_counted_as_dropped` | 例 1 计数副作用：reloc 行/节头/纯数据字节行属"跳过"而非"丢弃" |
| `test_ida_address_column_prefix_is_stripped` | 例 2（`CODE:` / 裸 8 位十六进制 / `.text:` 三形态） |
| `test_ida_semicolon_comment_is_stripped_before_operand_parse` | 例 3（操作数须仍是 `mem base=ecx disp=-4`，不得是 `other`） |
| `test_unparseable_body_leaves_insufficient_evidence_trace` | 缺口 4（非空零解析 ⇒ 必须留痕，不得空 notes） |
| `test_mostly_dropped_body_leaves_partially_parsed_trace` | 缺口 4（丢弃占比 > 50% ⇒ 留痕） |
| `test_empty_input_has_no_evidence_trace` | 反向门：真·空输入**不得**凭空产生痕迹 |

## F2. 红相（HEAD 实现 + 新测试）—— 命令与输出原文

```sh
cd /home/peng/workspace/PAL3Decomp
git show HEAD:tools/vtable_slot_classifier.py > /tmp/oldclf/vtable_slot_classifier.py
python3 - <<'PY'
import importlib.util, sys
spec = importlib.util.spec_from_file_location('vtable_slot_classifier', '/tmp/oldclf/vtable_slot_classifier.py')
mod = importlib.util.module_from_spec(spec)
sys.modules['vtable_slot_classifier'] = mod          # 抢在 tests 的 sys.path(tools) 之前注册旧实现
spec.loader.exec_module(mod)
src = open('tests/test_vtable_slot_classifier.py', encoding='utf-8').read()
try:
    exec(compile(src, 'tests/test_vtable_slot_classifier.py', 'exec'),
         {'__name__': '__main__', '__file__': 'tests/test_vtable_slot_classifier.py'})
except SystemExit:
    pass
PY
```

输出原文（`FAIL` 行 + 结论行）：

```
  FAIL test_ida_address_column_prefix_is_stripped: AssertionError: ('\nCODE:00401000 sub ecx,[ecx-4]\nCODE:00401003 jmp loc_body\n', (Insn(mnem='code', ops=(Operand(kind='other', reg='', base='', index='', scale=0, disp=0, value=0, text=':00401000 sub ecx'), Operand(kind='mem', reg='', base='ecx', index='', scale=0, disp=-4, value=0, text='[ecx-4]')), raw='CODE:00401000 sub ecx,[ecx-4]'), Insn(mnem='code', ops=(Operand(kind='other', reg='', base='', index='', scale=0, disp=0, value=0, text=':00401003 jmp loc_body'),), raw='CODE:00401003 jmp loc_body')))
  FAIL test_ida_semicolon_comment_is_stripped_before_operand_parse: AssertionError: Operand(kind='other', reg='', base='', index='', scale=0, disp=0, value=0, text='[ecx-4]  ; adjust this')
  FAIL test_mostly_dropped_body_leaves_partially_parsed_trace: AssertionError: ()
  FAIL test_objdump_reloc_annotation_lines_are_skipped: AssertionError: (Insn(mnem='sub', ops=(Operand(kind='reg', reg='ecx', base='', index='', scale=0, disp=0, value=0, text='%ecx'), Operand(kind='mem', reg='', base='ecx', index='', scale=0, disp=-4, value=0, text='-0x4(%ecx)')), raw='sub    -0x4(%ecx),%ecx'), Insn(mnem='jmp', ops=(Operand(kind='target', reg='', base='', index='', scale=0, disp=0, value=8, text='0x8'),), raw='jmp    0x8'), Insn(mnem='r_386_pc32', ops=(Operand(kind='other', reg='', base='', index='', scale=0, disp=0, value=0, text='?o@D@@$4PPPPPPPM@A@AEXXZ'),), raw='R_386_PC32  ?o@D@@$4PPPPPPPM@A@AEXXZ'))
  FAIL test_reloc_and_structural_lines_are_not_counted_as_dropped: AssertionError: SlotClassification(kind='fn', features=frozenset(), notes=())
  FAIL test_unparseable_body_leaves_insufficient_evidence_trace: AssertionError: 非空输入零解析不得静默返回空 notes
Results: 28 passed, 6 failed, 0 skipped
```

红相读数：**6 failed / 28 passed**（第 7 条 `test_empty_input_has_no_evidence_trace` 是反向门，
在 HEAD 上即绿——它钉的是"不要过度留痕"，非缺陷本体）。

## F3. 绿相 —— 命令与输出原文

```sh
cd /home/peng/workspace/PAL3Decomp
python3 tests/test_vtable_slot_classifier.py
```

输出原文（节选新增 7 条 + 结论行；全量 34 行 PASS）：

```
  PASS test_empty_input_has_no_evidence_trace
  PASS test_ida_address_column_prefix_is_stripped
  PASS test_ida_semicolon_comment_is_stripped_before_operand_parse
  PASS test_mostly_dropped_body_leaves_partially_parsed_trace
  PASS test_objdump_reloc_annotation_lines_are_skipped
  PASS test_reloc_and_structural_lines_are_not_counted_as_dropped
  PASS test_unparseable_body_leaves_insufficient_evidence_trace
Results: 34 passed, 0 failed, 0 skipped
```

**原 27 条不回退**（按测试名单独复跑，而非仅看总数）：只调用 §9 之前定义的 27 个 `test_*`：

```sh
cd /home/peng/workspace/PAL3Decomp
python3 - <<'PY'
import importlib.util, re
src = open('tests/test_vtable_slot_classifier.py', encoding='utf-8').read()
head_names = re.findall(r'^def (test_\w+)', src.split('# ================= 9.')[0], re.M)
spec = importlib.util.spec_from_file_location('t', 'tests/test_vtable_slot_classifier.py')
mod = importlib.util.module_from_spec(spec); spec.loader.exec_module(mod)
bad = []
for n in head_names:
    try: getattr(mod, n)()
    except Exception as e: bad.append((n, repr(e)))
print('originals:', len(head_names), '=>', 'ALL PASS' if not bad else bad)
alln = [n for n in dir(mod) if n.startswith('test_')]
print('total tests in file:', len(alln))
PY
```

输出原文：

```
originals: 27 => ALL PASS
total tests in file: 34
```

**同任务组 Task 1 未受影响**（未修改 `tools/vtable_slot_order.py`）：

```sh
python3 tests/test_vtable_slot_order.py
```
```
Results: 35 passed, 0 failed, 0 skipped
```

> ⚠️ 本环境 `pytest` 仍损坏（见正文顾虑 6，`TypeError: required field "lineno" missing from alias`），
> 故一律以文件内独立运行器 / `importlib` 复跑验证。

## F4. 真实数据端到端（**只用原始指令字节**，未读 decomp JSON）

### F4.1 例 1 用**真** `objdump -dr`（内联 `R_386_PC32`）

注：PE-COFF 的 `objdump -dr` 把重定位放在独立 `RELOCATION RECORDS FOR [...]` 段、**不内联**
（实测 `vt3.obj`），内联 `R_386_PC32` 形态只在 ELF 可重定位目标上出现 ⇒ 用真 objdump 产出该形态：

```sh
mkdir -p /tmp/t2reloc && cd /tmp/t2reloc
cat > t.s <<'EOF'
.globl _thunk_vbase
_thunk_vbase:
	sub -4(%ecx),%ecx
	jmp _target_vbase
.globl _thunk_static
_thunk_static:
	sub $8,%ecx
	jmp _target_static
EOF
gcc -m32 -c t.s -o t.o && objdump -dr t.o > listing.txt
```

`listing.txt` 逐字（真工具输出，非手写）：

```
00000000 <_thunk_vbase>:
   0:	2b 49 fc             	sub    -0x4(%ecx),%ecx
   3:	e9 fc ff ff ff       	jmp    4 <_thunk_vbase+0x4>
			4: R_386_PC32	_target_vbase

00000008 <_thunk_static>:
   8:	83 e9 08             	sub    $0x8,%ecx
   b:	e9 fc ff ff ff       	jmp    c <_thunk_static+0x4>
			c: R_386_PC32	_target_static
```

逐函数切片后 HEAD vs 修复版（复现脚本，`/tmp/oldclf/vtable_slot_classifier.py` = HEAD 版）：

```sh
cd /home/peng/workspace/PAL3Decomp
python3 - <<'PY'                                   # E2E-1
import importlib.util, sys, re, subprocess
def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m); return m
old = load('old_clf', '/tmp/oldclf/vtable_slot_classifier.py')
new = load('new_clf', 'tools/vtable_slot_classifier.py')

lines = open('/tmp/t2reloc/listing.txt', encoding='utf-8').read().splitlines()
def slice_fn(text_lines, sym):
    start = 0
    for i, l in enumerate(text_lines):
        if re.match(r'^[0-9a-f]+ <%s>:' % sym, l.strip()):
            start = i; break
    out = []
    for l in text_lines[start + 1:]:
        if re.match(r'^[0-9a-f]+ <.+>:', l.strip()):
            break
        out.append(l)
    return '\n'.join(out)

for sym, expect in (('_thunk_vbase', 'adjustor_vbase'), ('_thunk_static', 'adjustor_static')):
    body = slice_fn(lines, sym)
    o = old.classify_slot(old.SlotEvidence(instructions=body))
    n = new.classify_slot(new.SlotEvidence(instructions=body))
    print('%-14s HEAD: kind=%-15s notes=%s' % (sym, o.kind, list(o.notes)))
    print('%-14s FIX : kind=%-15s notes=%s' % ('', n.kind, list(n.notes)))
    assert o.kind == 'fn' and n.kind == expect
print('E2E-1 OK：真 objdump -dr（含 R_386_PC32）—— HEAD 静默 fn ⇒ 修复后判 thunk\n')
PY
```

输出原文：

```
_thunk_vbase   HEAD: kind=fn              notes=[]
               FIX : kind=adjustor_vbase  notes=['adjustor_vbase: 动态 delta 调整 + 尾 jmp（vbtable 相对/间接）']
_thunk_static  HEAD: kind=fn              notes=[]
               FIX : kind=adjustor_static notes=['adjustor_static: `add/sub imm,%ecx; jmp` 序言（仅 ecx 操作数）']
E2E-1 OK：真 objdump -dr（含 R_386_PC32）—— HEAD 静默 fn ⇒ 修复后判 thunk
```

### F4.2 真实函数体回归安全网：72 个真机函数 HEAD vs FIX **零差异**

对 `vt2/vt3/q2a/q2b/c2.obj` 的**完整** `objdump -dr` 清单按符号头切分，逐函数（含符号名一起）跑
两版实现，比较 `(kind, notes)` 全等：

```sh
cd /home/peng/workspace/PAL3Decomp
python3 - <<'PY'                                   # E2E-2
import importlib.util, re, subprocess
def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m); return m
old = load('old_clf', '/tmp/oldclf/vtable_slot_classifier.py')
new = load('new_clf', 'tools/vtable_slot_classifier.py')
HDR = re.compile(r'^[0-9a-f]+ <(.+)>:')
tot = diff = 0
for obj in ('vt2', 'vt3', 'q2a', 'q2b', 'c2'):
    text = subprocess.run(['objdump', '-dr', '/tmp/t2probe/%s.obj' % obj],
                          capture_output=True, text=True).stdout
    funcs, cur, nm = [], [], None
    for l in text.splitlines():
        m = HDR.match(l.strip())
        if m:
            if nm: funcs.append((nm, '\n'.join(cur)))
            nm, cur = m.group(1), []
        elif nm is not None:
            cur.append(l)
    if nm: funcs.append((nm, '\n'.join(cur)))
    for nm, body in funcs:
        tot += 1
        o = old.classify_slot(old.SlotEvidence(symbols=(nm,), instructions=body))
        n = new.classify_slot(new.SlotEvidence(symbols=(nm,), instructions=body))
        if (o.kind, o.notes) != (n.kind, n.notes):
            diff += 1
            print('DIFF %-6s %-44s HEAD=%s FIX=%s' % (obj, nm[:44], o.kind, n.kind))
print('E2E-2 真机函数体回归: classified=%d, behavior differences HEAD->FIX=%d' % (tot, diff))
PY
```

输出原文：

```
E2E-2 真机函数体回归: classified=72, behavior differences HEAD->FIX=0
```

⇒ 本修复对**原本能正确解析的输入是纯增量**（不改变任何既有结论），只修静默失败的路径。

## F5. 解析完整性计数在真实清单上的表现（`parse_disasm_report`）

```sh
cd /home/peng/workspace/PAL3Decomp
python3 - <<'PY'
import sys, subprocess
sys.path.insert(0, 'tools')
from vtable_slot_classifier import parse_disasm_report
cases = [('ELF objdump -dr（内联 reloc）', open('/tmp/t2reloc/listing.txt', encoding='utf-8').read()),
         ('PE-COFF vt3.obj objdump -dr',
          subprocess.run(['objdump', '-dr', '/tmp/t2probe/vt3.obj'],
                         capture_output=True, text=True).stdout)]
for label, t in cases:
    r = parse_disasm_report(t)
    print('%-30s content=%d parsed=%d skipped=%d dropped=%d insuff=%s partial=%s'
          % (label, r.content_lines, r.parsed_lines, r.skipped_lines, r.dropped_lines,
             r.insufficient_evidence, r.partially_parsed))
PY
```

输出原文：

```
ELF objdump -dr（内联 reloc）    content=10  parsed=4   skipped=11  dropped=0  insuff=False partial=False
PE-COFF vt3.obj objdump -dr      content=132 parsed=112 skipped=36  dropped=0  insuff=False partial=False
```

⇒ 真实清单**不误报** `insufficient_evidence` / `partially_parsed`。
（实现中另修一处计数语义：PE-COFF 的**纯数据字节续行** `  16:\t00` / `  16:\t00 00 00 00`
无指令文本，属"跳过"而非"丢弃"——否则数据密集的 COMDAT 切片会误报 `partially_parsed`；
实测 vt3.obj 上这类行 5 条，修前 `dropped=5`，修后 `dropped=0`。）

## F6. 实现改动摘要（`tools/vtable_slot_classifier.py`）

| 改动 | 内容 |
|---|---|
| 新增 `_RELOC_LINE` | `^\s*(?:<offset>:\s*)?R_[A-Za-z0-9_]+\b` ⇒ `R_386_*` / `R_IA64_*` … 通用（不写死架构） |
| `;` 注释剥离 | 解析主循环首步 `line = raw.split(';', 1)[0]`（分号在字符串中的情形按简报忽略） |
| 新增 `_IDA_ADDR_COL` + `_strip_ida_addr_column()` | 剥 `CODE:00401000 ` / `.text:00401000 ` / `00401000  ` 前缀，**可重复**剥；纯十六进制字母词（x87 `fadd`）不剥，避免吞真指令 |
| 新增 `ParseReport` + `parse_disasm_report()` | 指令 + `content/parsed/skipped/dropped` 计数 + `insufficient_evidence` / `partially_parsed` 判据 |
| `parse_disasm()` | 改为 `parse_disasm_report(text).insns` —— **对外签名/返回类型不变**（Task 3 可继续用） |
| `classify_slot()` | 文本输入时附解析完整性痕迹；`insufficient_evidence` / `partially_parsed` **显式点出"回落 fn 不可信，需 IDA 人工复核"** |
| 删除 `_as_insns` | 被 `_as_insns_and_report` 取代（无外部消费者，避免死代码） |
| `_split_objdump_rest` | 纯数据字节行 ⇒ 返回 `''`（视作纯字节续行跳过），修 F5 的计数语义 |

**kind 语义未扩**：证据不足时 kind 仍为 `fn`（无正特征可归），但 **notes 不再是空的**——
"静默 fn"这条最危险的失败模式被消除；是否需要更强的 `needs_manual_review` 由上层裁定（见 F7）。

## F7. 顾虑 / 遗留

1. **`insufficient_evidence` 只留痕、不改 kind**：按简报"在 notes 里加标记"实现，kind 保持 `fn`。
   若上层希望这类槽**不得**当普通函数消费（例如 Task 3 跳过合成槽时把 `fn` 当安全默认），
   建议二选一：① 把 `needs_manual_review` 也置 True；② 新增 kind 词面。**当前未做，以免越权改词表。**
2. **`;` 剥离是"简单模式"**：字符串内含分号的场景（本场景不存在）会误剥。objdump 不用 `;` 作注释符号，
   故只对 IDA 语法有意义。
3. **地址列判据含"必须含十进制数字"这一启发式**：为放过 x87 `fadd`（4 个 hex 字母）而加。
   若将来遇到纯字母十六进制地址（如 `FADD` 单独成列），会漏剥 ⇒ 该行退化为 `dropped` 并留痕，不会静默。
4. **`_RELOC_LINE` 只认 `R_<ARCH>_<TYPE>` 前缀**：`objdump -dr` 若改用其它重定位书写（如 `# R_386_32`
   前置 `#`）不会被跳过 ⇒ 仍会伪解析。已按简报范围实现；如需覆盖，加一条正则即可。
5. **本环境 pytest 损坏**（正文顾虑 6 仍在）：新测试只能经文件内运行器 / `importlib` 验证；
   CI 上若 pytest 可用，这 34 条是普通 `test_*` 函数，可直接被收集。
6. **PE-COFF 无内联 reloc**（F4.1 注）：本例 1 的端到端用 ELF i386 复现内联形态；若未来对
   `.obj` 直接跑 `objdump -dr`，重定位出现在独立段落，需要另行解析 `RELOCATION RECORDS` 才能
   把"哪个槽指到哪个符号"接上——**那是 Task 3/后续任务的范围，本修复不涉及**。

---

# 追加修复记录 R=2：PE-COFF 重定位注释行（`dir32` / `DISP32`）崩溃缺陷（2026-09-25）

> 承接上文 F1–F7（R=1，2026-09-24）。R=2 关闭 **F7 顾虑 4** 中明确预留的缺口
> （原文："`_RELOC_LINE` 只认 `R_<ARCH>_<TYPE>` 前缀 … 如需覆盖，加一条正则即可"），
> 并把 Task 3 的 workaround 从"唯一防线"降级为"冗余纵深防御"。

## F8. 缺陷一句话

`parse_disasm_report` 在 **PE-COFF `objdump -dr` 的重定位注释行**上抛 `ValueError`：

```
>>> parse_disasm_report("  6f:\t68 00 00 00 00       \tpush   $0x0\n  70:\tdir32\t$SG263\n")
ValueError: invalid literal for int() with base 10: 'sg263'
```

**根因**：`_RELOC_LINE` 只认 GNU ELF 的 `R_<ARCH>_<TYPE>`（`R_386_32` 能过），而真实 PE-COFF
objdump 打印 **howto 类型名**（`dir32` / `DISP32` / `off32`）⇒ 该行进入指令解析 ⇒ x86 PE 的
**字符串符号带 `$` 前缀** ⇒ `_att_operand('$SG263')` → `_parse_int('sg263')` → `ValueError`。

**失效模式比 R=1 三例更烈**：R=1 是"静默丢弃 ⇒ 误判 fn"；R=2 是**直接崩溃**（异常穿出整个
解析 → 该槽/该批函数全部无法判定）。真实二进制里凡"字符串地址压栈"的函数都有这种行。

## F9. 红相 —— 命令与输出原文

新测试先写（4 条，见 F12），在 HEAD 实现上运行：

```
$ python3 tests/test_vtable_slot_classifier.py 2>&1 | grep -E "FAIL|Results:"
  FAIL test_dollar_prefixed_non_numeric_operand_falls_back_to_other: ValueError: invalid literal for int() with base 10: 'sg240'
  FAIL test_pe_coff_dir32_reloc_line_is_skipped_not_parsed_as_insn: ValueError: invalid literal for int() with base 10: 'sg240'
  FAIL test_pe_coff_reloc_line_does_not_steal_last_insn_position: ValueError: invalid literal for int() with base 10: 'sg240'
  FAIL test_pe_coff_reloc_type_name_forms_are_all_skipped: AssertionError: ('dir32', (Insn(mnem='call', ops=(Operand(kind='target', …, text='3b <_main+0x1b>'),), raw='call   3b <_main+0x1b>'), Insn(mnem='dir32', ops=(Operand(kind='other', …, text='?log@S@@UAEHPBDH@Z'),), raw='dir32\t?log@S@@UAEHPBDH@Z'), Insn(mnem='ret', ops=(), raw='ret')))
Results: 34 passed, 4 failed, 0 skipped
```

⇒ 4 条新测试**全红**；原 34 条**全绿**（未回退）。第 4 条的失败形态还暴露了**第二种**损坏：
`dir32` 本身被当成助记符（符号操作数不带 `$` 时不崩溃，而是静默多出一条伪指令 ⇒ 可抢占末位，
正是 R=1 防范的"误判 fn"模式）。

## F10. 绿相 —— 命令与输出原文

```
$ python3 tests/test_vtable_slot_classifier.py 2>&1 | grep -E "pe_coff|dollar|Results:"
  PASS test_dollar_prefixed_non_numeric_operand_falls_back_to_other
  PASS test_pe_coff_dir32_reloc_line_is_skipped_not_parsed_as_insn
  PASS test_pe_coff_reloc_line_does_not_steal_last_insn_position
  PASS test_pe_coff_reloc_type_name_forms_are_all_skipped
Results: 38 passed, 0 failed, 0 skipped

$ python3 -c "import sys; sys.path.insert(0,'tools'); from vtable_slot_classifier import parse_disasm_report; \
  r = parse_disasm_report('  6f:\t68 00 00 00 00       \tpush   $0x0\n  70:\tdir32\t$SG263\n'); \
  print([i.mnem for i in r.insns], 'skipped=%d dropped=%d' % (r.skipped_lines, r.dropped_lines))"
['push'] skipped=1 dropped=0          # 简报里的原始复现式，修后不再抛异常
```

**零回退**：R=1 的 34 条全绿（`38 = 34 + 4`）。

## F11. 真机证据（PE-COFF `dir32` 逐字，非构造）

R=1 的夹具来自 **ELF i386** 复现（见 F4.1 注）；本轮补上**真 PE-COFF** 逐字证据：

```cpp
// /tmp/pe_reloc_probe/p1.cpp
int printf(const char *, ...);
struct S { virtual int log(const char *s, int v); };
int S::log(const char *s, int v) { printf(s, v); return v; }
int g(void);
int main() { S s; s.log("a", 1); return g(); }
```
```bash
# 真机 MSVC 6.0 SP0（cl 12.00.8168）
tools/wine_cl.sh /c /nologo /Od /GR /Fo/tmp/pe_reloc_probe/p1.obj /tmp/pe_reloc_probe/p1.cpp
objdump -dr /tmp/pe_reloc_probe/p1.obj > p1.dr.txt     # GNU binutils 2.38，pe-i386
```

重定位行逐字形态（`cat -A`，`^I` = TAB）：

```
  2c:^I6a 01                ^Ipush   $0x1$
  2e:^I68 00 00 00 00       ^Ipush   $0x0$
^I^I^I2f: dir32^I$SG240$
  33:^I8d 4d fc             ^Ilea    -0x4(%ebp),%ecx$
```

⇒ 三处关键事实（父任务 A 方案的判据来源）：
1. 前缀是 `\t\t\t<offset>: `（**TAB 缩进**，不是空格），`<offset>` 是操作数末字节偏移（`2f` 而非 `2e`）；
2. 类型名是 **`dir32`**（小写）/ **`DISP32`**（大写，call 目标）；**不带 `R_` 前缀**；
3. x86 PE 字符串符号**带 `$`** ⇒ `$SG240`；vtable 符号形如 `??_7S@@6B@-0x4`（**无 `$`**，故不崩但会静默伪解析）。

**同一真机清单（56 行）端到端，HEAD vs FIX**：

```
# HEAD（git stash 掉本轮改动后）
HEAD (pre-fix): ValueError invalid literal for int() with base 10: 'sg240'

# FIX
raw=56 content=49 parsed=37 skipped=19 dropped=0
dropped_examples: ()
partially_parsed=False insufficient_evidence=False
spurious mnem: []          # 助记符集合里不含 dir32/DISP32/disp32/off32/secrel32
```

⇒ 修复前**整份真实清单解析崩溃**；修复后 37 条真指令、0 行丢弃、无伪助记符、不误报
`partially_parsed` / `insufficient_evidence`。

## F12. 实现改动摘要（`tools/vtable_slot_classifier.py`）

| 方案 | 改动 | 内容 |
|---|---|---|
| **A（治本）** | `_RELOC_LINE` 扩名 | `...R_[A-Za-z0-9_]+\b\|(?i:dir32\|disp32\|off32\|secrel32)\b` —— 保留 `offset:` 前缀可选、带不带都算；用 `(?i:…)` **局部**大小写不敏感，不动 `R_*` 分支既有语义 |
| **B（兜底）** | `_att_operand` 的 `$` 分支 | `$` 后先过 `_INT_RE`，**非数字**（未解析符号）⇒ `Operand('other')`；数字/`h` 后缀/负数/0x 写法**仍走 imm**（不因兜底放宽而回退） |

**名表取舍（逐条证据分级）**：

* `dir32` / `DISP32` —— **A 级**：本机真机发射（F11 逐字）；
* `secrel32` —— **B 级**：`grep -a -o -E '\b(dir32|secrel32)\b' libbfd-2.38-system.so` 命中该名（同 howto 表）；漏掉它**不崩**但会静默多出一条伪指令 ⇒ 属同类风险，一并收进；
* `off32` —— **C 级（任务指定）**：本机 objdump 2.38 pe-i386 **未发射**该名；Task 3 `_PE_RELOC_LINE` 亦已列入 ⇒ 按同族收进，标注为待后续真机确认。

新增测试（`tests/test_vtable_slot_classifier.py` §10，4 条）：
① `test_pe_coff_dir32_reloc_line_is_skipped_not_parsed_as_insn`（11 行真机 `_main` 逐字夹具：8 指令 / 3 跳过 / 0 丢弃）；
② `test_pe_coff_reloc_type_name_forms_are_all_skipped`（`dir32`/`DISP32`/`disp32`/`off32`/`secrel32` 五形态）；
③ `test_pe_coff_reloc_line_does_not_steal_last_insn_position`（末位不被抢占 ⇒ `adjustor_vbase` 不误判 fn）；
④ `test_dollar_prefixed_non_numeric_operand_falls_back_to_other`（`push $SG240` 回落 `other`；`$8`/`$0fh`/`$-1`/`$0xfffffff8` 仍为 imm）。

## F13. 跨模块影响：Task 3 的两条测试**必须**翻转（已在本次一并修）

`tests/test_vtable_sig_infer.py` §15 是 R=1 的"发现项留证"，**断言 Task 2 抛 `ValueError`**；
根因修复后它把**已修复的缺陷固化**下来 ⇒ 不翻转就是明知故犯的红灯。已改（**未动
`tools/vtable_sig_infer.py`，遵守 Task 3 产物禁改**）：

| 原测试 | 现测试 | 断言翻转 |
|---|---|---|
| `test_task2_parser_raises_on_pe_coff_dir32_reloc_line`（`assertRaises(ValueError)`） | `test_task2_parser_no_longer_raises_on_pe_coff_dir32_reloc_line` | 6 指令 / 3 跳过 / 0 丢弃，不抛异常 |
| `test_infer_does_not_crash_on_pe_coff_reloc_text_and_leaves_trace`（要求 `parser_error` 痕迹 + C 级） | `test_infer_accepts_pe_coff_reloc_text_without_parser_error` | **无** `parser_error`；原材料与 `sanitize_pe_relocs` 后结论**逐字相同**；仍 C 级 |

三套 vtable 测试全绿：`test_vtable_slot_classifier.py 38 passed` ·
`test_vtable_sig_infer.py 58 passed`（基线 58，翻前后各 2 红 → 翻后 0 红）·
`test_vtable_slot_order.py 35 passed`（Task 1，未受影响）。

**发现（记录，不在本任务范围）**：Task 3 `_PE_RELOC_LINE` 能 sanitize 的行集合是 Task 2
`_RELOC_LINE` 的**子集**（`R_386_`/`R_IA64_`/`R_X86_64_` ⊆ `R_*`；`DISP32`/`dir32`/`off32`
被大小写不敏感覆盖）⇒ 不再存在"Task 2 抛异常、Task 3 能兜住"的行 ⇒ Task 3 的
`FEATURE_PARSER_ERROR` 分支对该输入**成为不可达代码**（保留即可，勿删）。另一处
`_safe_parse`/`_safe_classify` 的 `except ValueError` 若 sanitize 后**仍抛**会让异常穿出
⇒ 兜底只对"能被 sanitize 的行"成立；Task 2 修复后该路径对本缺陷已无意义，但**非 reloc 形态**
的 `ValueError`（见 F14.2）仍会穿透 —— 属 Task 3 自身缺口，需上层决定是否跟进。

## F14. 顾虑 / 遗留

1. **`off32` 无本机真机证据（C 级）**：本机 objdump 2.38 pe-i386 只发射 `dir32`/`DISP32`
   （`off32` 疑似 x86-64 PE 或其它 coff 目标的 howto 名）。已按任务指定 + Task 3 同名列入；
   **拿到发射 `off32` 的 objdump/目标后应补一条逐字夹具**（当前只能证明"列进去无害"，不能证明"真发射"）。
2. **B 案只护住 `$` 分支，同类崩溃点仍在**：`_att_operand` 的**内存操作数 head**
   （`symbol(%eax)` → `tools/vtable_slot_classifier.py:237` 的 `_parse_int(head)`）与
   `_parse_mem_expr` 的非数字位移项（同文件 `:207`、`:214` 的 `disp += sgn * _parse_int(term)`）
   同样会抛 `ValueError`。已实测（本轮，见 F14 末"验证原文"）：
   `parse_disasm('mov ?x@@YAHXZ(%ecx),%eax')` 仍抛
   `ValueError: invalid literal for int() with base 10: '?x@@yahxz'`。
   **未扩到该处**是因为（i）简报把 B 案限定在 `$` 后非数字；（ii）objdump 对符号
   操作数不打印 `sym(%reg)` 形态（先验证据不足）⇒ 不愿在无实测形态时放宽语义。
   若上层要求"解析器整体不崩"，应把这两处一并按 `other` 回落（或给 `parse_disasm_report`
   加"留痕而不抛"的边界），**这是 R=3 的候选**。
3. **`_RELOC_LINE` 名表是"白名单"而非"形状判据"**：PE-COFF 还有 `addr32`/`dir32nb`/`seg12` 等
   候选名（`dir32nb` 未在 libbfd-2.38 命中 ⇒ **未收**，避免凭空发明形态）。若遇到新的 howto 名
   仍会退化为"静默多一条伪指令"（**不崩**）。更稳的判据是"行形如 `<offset>: <name32>\t<sym>`
   且 `<offset>` ≤ 上一指令偏移+长度"——但那需要跨行状态，超出本次"小而具体"的范围。
4. **本环境 pytest 损坏**（R=1 顾虑 5 仍在，本轮复验）：`python3 -m pytest tests/…` 报
   `TypeError: required field "lineno" missing from alias`（`_pytest/assertion/rewrite.py:360`，
   环境级问题，与本改动无关）⇒ 本轮全部经文件内运行器 `python3 tests/<file>.py` 验证。
5. **改动文件超出简报的 2 个**：简报指定 `git add tools/vtable_slot_classifier.py
   tests/test_vtable_slot_classifier.py`；因 F13 的"固化已修缺陷"必须翻转，`tests/test_vtable_sig_infer.py`
   一并提交（**工具本体 `tools/vtable_sig_infer.py` 与 `tools/vtable_slot_order.py` 均未改动**）。

### F14 末：顾虑 2 / F13 的验证原文（本轮实测，逐字）

```
$ python3 -c "..."   # 探针：B 案未覆盖的同类崩溃点 + Task 3 兜底穿透
'mov ?x@@YAHXZ(%ecx),%eax' -> RAISED ValueError invalid literal for int() with base 10: '?x@@yahxz'
'mov sym(%ecx),%eax'       -> RAISED ValueError invalid literal for int() with base 10: 'sym'
'push $SG240'              -> (Insn(mnem='push', ops=(Operand(kind='other', …, text='$SG240'),), raw='push $SG240'),)
_safe_parse: RAISED ValueError invalid literal for int() with base 10: '?x@@yahxz'
```

⇒ 逐条坐实：①`$` 分支已回落 `other`（方案 B 生效）；②`sym(%reg)` 形态**仍崩**（顾虑 2 的范围外遗留）；
③Task 3 `_safe_parse` 对该形态**sanitize 后仍抛 ⇒ 异常穿出**（F13 记录的 Task 3 自身缺口）。

### F14 末：三套测试最终状态（逐字）

```
$ python3 tests/test_vtable_slot_classifier.py   → Results: 38 passed, 0 failed, 0 skipped   (R=1 的 34 + 新 4)
$ python3 tests/test_vtable_sig_infer.py        → Results: 58 passed, 0 failed, 0 skipped   (基线 58；翻前 56 pass/2 fail)
$ python3 tests/test_vtable_slot_order.py       → Results: 35 passed, 0 failed, 0 skipped   (Task 1 产物，未改动)
```
