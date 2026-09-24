# Task 4 交付报告：布局断言生成器（默认启用）

- **状态**：**DONE_WITH_CONCERNS**
- **交付**：`tools/layout_assert_gen.py`（生成器 + CLI）· `tests/test_layout_assert_gen.py`（46 测）·
  `data/status/_layout_assert_probe_20260925/`（金样本 + 编译器裁判 + 二进制佐证）
- **一行测试摘要**：**新 46 passed / 0 failed** · 8 个变异体全被杀死 · 前序 vtable 三套测试无回退（35/38/66）·
  真机 MSVC6 编译器裁判 `verify_generated_asserts.py` **ALL CHECKS PASSED**（正相 31 条生效断言 0 错误；
  4 类负相全被 C2118；虚基成员 C2057；重名重定义族）
- **提交**：（见文末「提交」）——`.superpowers/sdd/` 被仓库 `.gitignore` 排除，本报告只落盘不入库

> **无子代理**：本任务全程未分发任何子代理（符合"无子代理契约"）。
> **未触碰管线**：只新增工具/测试/探针；不改 annotation、apply、export、codegen、stage*。
> 生成器**只读** `data/annotations/**`，`main()` 硬拒 `--out` 落在该目录下（实测 exit 2）。

---

## 1. 需求对照

| 需求（简报） | 实现 | 证据 |
|---|---|---|
| 输出 `_layout_asserts.h`（MSVC6 负数组技巧） | `render_header()`：`typedef char NAME[(COND) ? 1 : -1];`，CLI 默认 `--out _layout_asserts.h` | 探针正相：31 条生效断言编译 **0 错误** |
| PMF 形状断言**按实际继承形状**生成，不硬编码 4 | `shape_info()`：**虚基⇒12 / 闭包内多继承分支⇒8 / 否则4** | `verify_generated_asserts.py` 由编译器**自己发现** 10 个形状常量，与规则逐一相符 |
| 虚基成员**跳过** offsetof（C2057） | `member_offset_assertable()`：跳过 `in_virtual_base` / `owner ∈ 虚基传递闭包` / offset 落在记录的虚基区间 | `off.cpp:15/17/18` 三条 C2057；朴素生成器（不跳）实测 C2057 |
| 断言常量源自二进制 A 级证据，非同源 annotation | `Evidence(grade, origin, independent, misattributed)` + `trusted/same-source/suspect` 三态 + `--evidence` 独立证据入口 | E-1/E-2 各有测试；真实数据默认下 68 条同源、10674 条可疑**均不生效**，只留痕 |
| `#include <stddef.h>` / 类型名全局唯一 | 无条件注入；`NameRegistry` 全局去重 | `p2.cpp` 缺它 ⇒ C2065；重名 ⇒ C2369/C2372 |
| TDD（先测试红 → 实现 → 绿） | 红 1：`ModuleNotFoundError`；红 2：骨架 **44 failed**；绿：**46 passed** | §4 |
| 交付报告 `task-4-report.md` | 本文件 | — |

**超出简报、但被实测逼出来的 3 条**（详见 §3）：闭包判据、虚基**传递**区域、可疑常量的默认"留痕不生效"。

## 2. 交付 API（供 Task 5/8 消费）

```python
from layout_assert_gen import (ClassLayout, BaseSpec, MemberSpec, Evidence, GenOptions,
                               generate, build_assertions, load_struct_layouts,
                               load_virtual_bases, load_evidence,
                               shape_info, pmf_size_for, virtual_base_region,
                               member_offset_assertable, evidence_from_source)

layouts = load_struct_layouts('data/annotations/structs',
                              tree_path='data/status/_inheritance_tree.json',
                              virtual_bases=load_virtual_bases(vb_json),   # 可选：虚基覆盖
                              evidence=load_evidence(ev_json))             # 可选：独立证据
res = generate(layouts, GenOptions(untrusted_policy='comment'))
res.text        # _layout_asserts.h 全文
res.assertions  # 每条: kind/shape|size|offset, cls, name, condition, expected, evidence, trust, status
res.census      # {'total','active','commented','omitted','skipped','trusted','same-source','suspect',
                #  'by_kind','by_trust','skip_reasons'}
res.offset_skipped  # 被跳过（非常量表达式）的成员清单
```

`Evidence.trust()` 三态（**A 级是形态等级，不是独立性等级** —— E-2）：

| trust | 判据 | 默认动作（`--untrusted-policy=comment`） |
|---|---|---|
| `trusted` | 形态 A ∧ `independent` ∧ 未疑误归属 | 生成**生效**断言 |
| `same-source` | 形态 A 但同源 annotation ⇒ 零判别力 | 注释留痕 `[SAME-SOURCE]` |
| `suspect` | 形态非 A，或 `misattributed`（E-1） | 注释留痕 `[SUSPECT]` |

CLI：`--structs --tree --virtual-bases --evidence --out --untrusted-policy{comment,skip,assert}
--only --no-shape/--no-size/--no-offset --no-stddef --require-closed-world-shape --census-json
--check --quiet`。`--check` 与磁盘逐字比对（确定性/棘轮）；`--only` 只过滤**渲染**，闭包查表仍用全量。

## 3. 实测发现（每条都有探针出处）

### 3.1 ★ 闭包边界：`DERofMI2 : MI2`（单直接基）⇒ PMF **8**，不是 4

简报给的封闭规则（"基>1 ⇒ 8"）只覆盖**直接基**形状。本轮 `shape.cpp` 实测：

```
shape.cpp(28) : error C2118   ← t_DERofMI2_4   （预测 4 ⇒ 错）
shape.cpp(29) : （无错误）      ← t_DERofMI2_8   （真值 8）
shape.cpp(34) : error C2118   ← t_DERofDERofMI2_4
shape.cpp(32) : error C2118   ← t_DERofV_4（基含虚基 ⇒ 12）
```

⇒ 判据必须走**传递闭包**："闭包内出现多继承分支"。否则真实数据里
`CCBRoleState : SceneObj`（SceneObj 是 3 基类）会预测 4 而实际是 8 ⇒ **假 C2118 ⇒ 停摆**
（与攻击集 E-4 同型的停摆风险，只是发生在闭包深度方向）。
实现：`shape_info()`；测试：`test_single_base_whose_ancestor_is_mi_pmf_is_8` 等 4 条 + 变异体 M1 被杀死。

### 3.2 ★ 虚基区域是**传递**的：虚基的非虚基之成员同样 C2057

`off.cpp:18`（`offsetof(DV2, w)`，`w` 在虚基 `VBase2` 的非虚基 `V1` 里）⇒ **C2057**。
同时 `off.cpp:11/13/19` 证明：**有虚基的类里，本类成员与非虚基成员 `offsetof` 仍是常量**
（只报 C2118 值不符，无 C2057）。⇒ 跳过集合 = `虚基 ∪ 虚基的传递闭包`（`virtual_base_region`）；
少跳 ⇒ 停摆，多跳 ⇒ 静默丢覆盖。变异体 M2 被杀死。

### 3.3 ★ 可疑常量的默认动作必须是"留痕不生效"（E-1 的工程化）

E-1（`w1/w2.cpp`）的教训：被污染的证据常量会把**正确注解**判死，工程师唯一"合规"出路是把注解改坏。
故生成器默认：

* `trusted` ⇒ 生效；`suspect`/`same-source` ⇒ **注释掉 + 标记 + 原因**，并把"常量本身可疑"
  作为**独立分支**写进头文件错误处理表（`branch 2`），同时 `assert` 时可一键放开（`--untrusted-policy=assert`）。
* 形状断言在**形状不可证**时同样降级：未知基类、基类信息缺失**且多态**的类、以及
  **多继承被建模成内嵌成员**的类（UIEmote 的 `baseclass2`）。

### 3.4 真数据里的具体雷：UIEmote（独立二进制佐证）

`check_shape_against_binary.py` 读 `original/PAL3.exe.asm` + `PAL3.exe` 的 `.rdata` 原始字：

```
UIEmote ctor sub_44E530:
   mov dword ptr [esi+44h], offset off_56A9C0
   mov dword ptr [esi+44h], offset off_56B044
   off_56B044 内容 = 0044EB40 0044AB00 004AF760 00445E70 ⇒ **vtable**（代码地址，不是 vbtable 的小整数）
```

⇒ **二进制形状是多继承**（第二张 vtable 写在 +0x44），而注解把它记成内嵌成员
（`PAL3patch:multi_inheritance_as_embed`）⇒ **声明形状 ≠ 二进制形状**。
生成器对该类形状断言降级 `[SUSPECT]`：4（内嵌声明）与 8（真 MI 声明）都可能与 codegen 不符 ⇒ 不赌。
同一脚本对 `CEffSParticle`（`+0`/`+0x0C` 两次 vfptr 写入，次表 0x56FB28 亦是 vtable）
给出**多继承、无虚基 ⇒ PMF 8** 的独立佐证 —— 与该类的生效断言一致。

### 3.5 简报收窄：同名 typedef 不是 C2086

`dup2.cpp` 实测：`C2371`（基本类型不同）/ `C2369`（数组尺寸不同）/ `C2040`、`C2372`（间接层冲突）；
**C2086 未出现**；且**类型完全相同**的冗余 typedef 被 MSVC6 **接受**（0 错误）。
⇒ "同名 ⇒ C2086"按实测收窄为"同名 ⇒ 重定义族错误（视冲突形态而定）"。
命名唯一性要求**仍然成立并已实现**（一条通过一条失败时错误码交织、定位含混；改用尺寸型数组即变硬错误）。

### 3.6 `offsetof` 需要 `#include <stddef.h>`（硬前置）

`p2.cpp` 缺它 ⇒ `C2065: 'offsetof' : undeclared identifier` + `C2275` + 连带 `C2057` 噪声
⇒ 真错误被掩盖。生成头无条件注入（`--no-stddef` 可关，仅用于自检）。

## 4. TDD 记录与判别力

| 阶段 | 命令 | 读数 |
|---|---|---|
| 红 1 | `python3 tests/test_layout_assert_gen.py` | `ModuleNotFoundError: No module named 'layout_assert_gen'` |
| 红 2（骨架：数据模型 + 词表 + `NotImplementedError`） | 同上 | **0 passed, 44 failed**（逐条"功能缺失"） |
| 绿 | 同上 | 33 passed / 11 failed（真失败：闭包判据、`0Ch` 形态证据、渲染未过滤 omitted 等） |
| 绿（修完） | 同上 | **45 passed** |
| 绿（补 `--only` 闭包缺陷测试） | 同上 | **46 passed, 0 failed, 0 skipped** |

**前序回归**（未触碰其产物）：`test_vtable_slot_order.py 35` / `test_vtable_slot_classifier.py 38` /
`test_vtable_sig_infer.py 66` 全绿。

**变异检验**（8 个变异体，全部被杀 —— 证明测试有判别力，非事后补测）：

| 变异体 | 结果 | 被杀测试（节选） |
|---|---|---|
| M1 形状判据退回"只看直接基" | KILLED (43) | `..._ancestor_is_mi_pmf_is_8` · `golden_shape_matrix` · `deep_single_chain_below_mi` |
| M2 取消虚基成员跳过 | KILLED (42) | `member_of_virtual_base_is_skipped` · `member_of_nonvirtual_base_of_virtual_base_is_skipped` |
| M3 `misattributed` 不再判可疑 | KILLED (42) | `evidence_trust_matrix` · `misattributed...comments_out` |
| M4 typedef 名不去重 | KILLED (43) | `assertion_type_names_are_globally_unique` · `colliding_sanitized_class_names` |
| M5 不注入 `<stddef.h>` | KILLED (43) | `stddef_include_is_injected` · `real_data_generates_header...` |
| M6 忽略"多继承内嵌建模"痕迹 | KILLED (44) | `embed_modeled_multi_inheritance_shape_is_suspect` |
| M7 虚基不再优先于多继承 | KILLED (38) | `multiple_inheritance_plus_virtual_base_pmf_is_12` · `two_virtual_bases_stay_12_not_16` 等 6 条 |
| M8 suspect 也直接生效 | KILLED (40) | `misattributed...` · `same_source...` · `shape_assert_is_suspect_when_base_graph_incomplete` |

**编译器裁判**（`data/status/_layout_assert_probe_20260925/verify_generated_asserts.py`，≈30 次真机 MSVC6 编译，**EXIT 0**）：

```
常量发现（编译器自己给真值，非手抄）：pmf SI=4 MI2=8 MI3=8 VOnly=12 MIV=12 MIVV=12 VV=12
   DERofMI2=8 DERofSI=4 DERofV=12；size SI=8 MI2=16 N=12 NV=24 DV=20；offset … / NV.vv、DV.vv = NOT_CONSTANT
正相：生成头 31 条生效断言 ⇒ 0 错误
负相：sizeof/偏移/形状/闭包判据 4 类改错 ⇒ 全部 C2118
虚基：朴素生成器（不跳过）⇒ C2057（C2057+C2466）
重名：C2369 / C2372；同型重名 ⇒ 0 错误
ALL CHECKS PASSED
```

## 5. 真实数据端到端

```sh
python3 tools/layout_assert_gen.py --out /tmp/_layout_asserts.h \
    --census-json data/status/_layout_assert_probe_20260925/_layout_asserts.census.json
# wrote … | total=10918 active=176 commented=10742 omitted=0 skipped=2
#         (trusted=176 same-source=68 suspect=10674)
```

| 项 | 值 |
|---|---|
| 装载 | 898 个 struct JSON ⇒ **881 类**（17 组同名去重，如 `HBRUSH_`/`HBRUSH__`）+ 继承树 179 条 |
| 断言 | total **10918** = shape 296 + size 881 + offset 9741 |
| 生效 | **176**（全部是形状断言） |
| 留痕不生效 | `[SAME-SOURCE]` 68（A 形态但同源）+ `[SUSPECT]` 10674（形态 C/归属存疑） |
| 跳过 | 2（`SceneMgr`/`tagCmdData` 的空成员名 ⇒ 无标识符可用） |
| 形状分档 | 176 生效（基类信息完整）+ 117 多态但无基类信息（降级可疑）+ 3 内嵌/未知基类 |

**为什么 size/offset 全不生效（这不是 bug，是 E-2 的必然结论）**：注解里的偏移常量与
生成头里成员声明**同源**（同一份 `known_members`）⇒ 断言恒真、零判别力；
A 形态的 68 条（`source` 含 `[ecx+0Ch]`/`0x00xxxxxx`）也只是"形态 A"，不是"独立"。
要让它们生效，必须经 `--evidence` 灌入**独立于 annotation 的 IDA 二进制读取**（Task 8 的活）。
`--require-closed-world-shape`（最保守口径）下 active 掉到 **1**：注解只覆盖 179/881 类的基类信息，
"闭包闭世界"在今天的注解集上几乎不可证。

**样张**：`_layout_asserts.sample.h`（6 类 / 235 行，含 5 条生效形状断言与 UIEmote 的 `[SUSPECT]` 降级）。

## 6. 病灶层检查（动手前的三个问题）

1. **病灶在哪一层**：本任务在**新工具层**（生成器），不碰管线。判据的唯一真值源是**真机编译器**
   （`verify_generated_asserts.py` 用 MSVC6 自己发现常量、自己判负相），不是"看起来对"。
2. **消费者实际读什么**：生成头消费者 = codegen 产出的头文件（须在**全部类声明之后** include，
   否则 C2027）；生成器消费者 = Task 5/8（`res.assertions`/`res.census` 结构化台账，不解析文本）。
3. **报错还缺什么信息**：`C2118` **只给行号不给常量名**（C2369/C2372 才给名），
   故生成器把 `kind|cls|member|expected|证据|trust|原因` 全部写进每行尾注释，
   并在头文件里固化**错误处理表**（branch 1 真布局错 / branch 2 常量本身可疑 / branch 3 生成器缺陷），
   避免"看到 C2118 就去改注解"。

## 7. 顾虑（需上层裁定 / 影响 Task 8）

1. **形状断言的语义是"声明一致性"，不是"二进制一致性"**：默认口径下形状常量来自
   E-4 探针（独立、A 形态），但**形状输入**（有几个基、哪个是虚基）来自 annotation。
   若 codegen 从 annotation 之外补基类（如 `template_bases.json` 或内嵌建模），
   生效的形状断言会**假失败**（E-1 同类风险）。缓解：`require_closed_world_shape` 极保守档 +
   `[SUSPECT]` 内嵌/未知基类降级；**根因解法**是 Task 8 用发射出的声明做输入。
2. **虚基信息在注解里根本不存在**：全仓 `structs/*.json` 没有任何虚基标记
   （只有 `bases[].offset` 与 `base_class`）。当前实现支持 `--virtual-bases` 覆盖文件 +
   `bases[].is_virtual/virtual` + `members[].in_virtual_base` 三种入口；**真实数据一条都没有**。
   ⇒ PAL3 是否真有虚基类，需 Task 8 用编译产物 vbtable 反查后回填；在那之前，
   任何"有虚基的类"都会被按 MI 处理（若真存在虚基类 ⇒ 12 vs 8 假失败）。
3. **独立证据通道尚未接上**：`--evidence` schema 已定（`{Cls: {size/members/shape: Evidence}}`），
   但仓库里还没有"IDA 二进制直接读取 → 证据 JSON"的生产者。在此之前，size/offset 断言
   在真实数据上只能留痕（E-2 的诚实结论）。
4. **`Evidence.independent` 由输入方声明**，生成器无法自证独立性（同源性是血缘问题）。
   默认把所有 annotation 来源标为非独立（保守），A 形态只影响"可疑"与"同源"的区分。
5. **`--only` 曾静默丢覆盖**（真实使用发现并已修）：过滤 layouts 会让闭包查不到基类 ⇒
   形状被误判"不可证" ⇒ 该类的生效断言全变注释。现已改为只过滤渲染 + 补测试
   `test_only_option_still_resolves_closure_for_shape`。**同类教训**：任何"缩小输入范围"的开关
   都必须区分"渲染范围"与"查表范围"。
6. **注解基类信息只覆盖 179/881 类**：`bases_known=False` 且多态的 117 类形状**不可证**
   （降级可疑）。这是注解覆盖度的度量，不是生成器缺陷；若要涨覆盖率，应补 `base_class`/继承树。
7. **全量头文件 12715 行 / 2.3 MB 不入库**（只入 census + 样张）；如上层要求入库，
   建议先决定 size/offset 的生效口径，否则提交的是 10742 行注释。
8. **未做管线集成**（Task 8 范围）：没有把 `_layout_asserts.h` 接进 codegen 的 include 链，
   也没有"生成 + 编译 + 归因"的闭环；`--check` 提供了棘轮式重放校验的原语。
9. **本环境 pytest 恒崩**（`_pytest/assertion/rewrite.py` 的 `TypeError: required field "lineno"
   missing from alias`，与 Task 1/2/3 记录一致）⇒ 46 条测试以文件内独立运行器验证；
   CI 上若 pytest 可用，它们是普通 `test_*` 函数，可直接收集。

## 8. 证据链自检

* 工具**只读** `data/annotations/**`（`main()` 硬拒写该目录，实测 exit 2）；不写 IDB；不发子代理。
* 3 条编译器规则全部来自**真机 MSVC6 SP0 实测**（`shape.cpp`/`off.cpp`/`p3.cpp`/`p2.cpp`/`dup2.cpp`），
  逐字输出入库 `data/status/_layout_assert_probe_20260925/README.md`。
* 形状输入的**独立佐证**来自 `original/PAL3.exe.asm`（IDA 二进制列表）与 `PAL3.exe` 的 `.rdata` 原始字，
  **不经 annotation**（`check_shape_against_binary.py`）。
* 8 个变异体全灭 ⇒ 测试有判别力；46 条测试中 5 条直接跑**真实 annotation 全量**（881 类）。

## 附录：复现

```sh
cd /home/peng/workspace/PAL3Decomp
python3 tests/test_layout_assert_gen.py                                    # 46 passed
python3 data/status/_layout_assert_probe_20260925/verify_generated_asserts.py   # 编译器裁判（≈1–2 min）
python3 data/status/_layout_assert_probe_20260925/check_shape_against_binary.py # 二进制佐证
python3 tools/layout_assert_gen.py --out /tmp/_layout_asserts.h \
    --census-json data/status/_layout_assert_probe_20260925/_layout_asserts.census.json
python3 tools/layout_assert_gen.py --only CEffSParticle,UIEmote,SceneObj,CCBUI,MUIDialog,Role \
    --out data/status/_layout_assert_probe_20260925/_layout_asserts.sample.h
python3 tools/layout_assert_gen.py --out /tmp/_layout_asserts.h --check   # 确定性重放
```

## 提交

- `tools/layout_assert_gen.py`（新增）
- `tests/test_layout_assert_gen.py`（新增）
- `data/status/_layout_assert_probe_20260925/`（新增：`shape.cpp` `off.cpp` `dup2.cpp`
  `verify_generated_asserts.py` `check_shape_against_binary.py` `README.md`
  `_layout_asserts.census.json` `_layout_asserts.sample.h` `_layout_asserts.sample.census.json`）
---

# R=1 修复轮（2026-09-25）—— 评审 3 Critical + 1 Important

- **状态**：**DONE**（3 Critical + 1 Important 全部修复；无豁免）
- **提交**：`1ce864e2f`（只含本任务 10 个文件；未纳入并行任务正在改的
  `pipeline/gen/stages/stage3_cleanup.py` / `tests/test_vtable_call_transform.py` 等）
- **一行测试摘要**：`tests/test_layout_assert_gen.py` **73 passed / 0 failed / 0 skipped**
  （R=0 的 46 条全部保留且绿 + 新增 27 条）；前序 `test_vtable_slot_order 35` /
  `test_vtable_slot_classifier 38` / `test_vtable_sig_infer 68` 全绿；
  **端到端裁判** `verify_emitted_asserts.py`：140 条真实生效断言 × 真实发射头 ⇒
  **0 假杀** / 132 PASS / 8 头文件自身编不过（与评审独立复算同一集合）
- **改动文件**：`tools/layout_assert_gen.py` · `tests/test_layout_assert_gen.py` ·
  `data/status/_layout_assert_probe_20260925/`（`ivb.cpp` `pmf_intro.cpp`
  `verify_emitted_asserts.py` `_emitted_asserts_judge.json` + README/census 更新）
- **未触碰**：annotation / apply / export / codegen / stage*（`git add` 只加自己的文件）

## R=1.1 逐项对照

| 项 | 缺陷（评审实测） | 修法 | 证据 |
|---|---|---|---|
| **C-1** 🔴 | `virtual_base_region` 只遍历**直接**虚基 ⇒ `VB2 : virtual V1; IVB : VB2` 返回 `[]` ⇒ `offsetof(IVB,vv)` 生效 | 遍历 `{layout} ∪ 闭包`，每个类的虚基 + 该虚基传递闭包进集合；**非虚**基不进 | `ivb.cpp:22` 逐字 **C2057+C2466**；`test_indirect_virtual_base_region_covers_whole_closure` 等 3 条 |
| **C-2** 🔴 | `load_struct_layouts` 把 `--virtual-bases` 与 `base_names` **求交** ⇒ `{'D':['V1']}` 静默丢弃（bases=[VB2]、pmf=4、region=[]、零 warning） | 覆盖名**加入** bases（含 `bases[].is_virtual` 里 base_class 未列的名字）；未知名额外 WARN + `bases_known=True` | `test_virtual_bases_override_adds_missing_base_instead_of_intersecting` 等 3 条（pmf 4→**12**、region={V1}） |
| **C-3** 🔴 | PMF 只按继承形状 ⇒ 漏 vfptr 引入点；`RoleCameraCtrl : PalScriptWaitObj` 真值 8 而生成器给 4（active/trusted）⇒ 真实头 C2118 | ①载体判据改用 `vtables`（新增 `ClassLayout.has_vtables`，`polymorphic` 不再混用）；②规则：最基层载体**有直接基 ⇒ 8**；③兜底：外部前缀（`gb*`）/ `--declared-classes` 名单外/闭包内出现这类基类 ⇒ **SUSPECT**；④新增**端到端裁判** | `pmf_intro.cpp`（`/FAs` 读编译器常量：INTRO⇒8 / SI_P⇒4 / INTRO_MID⇒8…）；`verify_emitted_asserts.py` **0 假杀**；退回旧规则 ⇒ 立刻抓到 `FALSE-KILL RoleCameraCtrl` |
| **I-2** 🟡 | size/offset 默认全注释 ⇒ 覆盖 1.6% | 新增独立 trust 档 `consistency-only` + 第 4 个 policy `--untrusted-policy consistency-only`（默认口径逐字不变）；仅对"声明由注解发射"的 size/offset 生效 | `test_consistency_only_tier_*` 5 条；真实数据该档 **8846** 条（默认 0 条） |

**不做（按裁定）**：I-1（6 个 `CEffTrack*` 重复间接基）转注解修复；I-3（接入 codegen include 链）归 Task 8。

## R=1.2 TDD 记录（先红后绿）

| 阶段 | 命令 | 读数 |
|---|---|---|
| 红 1 | `python3 tests/test_layout_assert_gen.py` | `ImportError: cannot import name 'MARK_CONSISTENCY_ONLY'` |
| 红 2（骨架：词表 + 数据类字段，无行为） | 同上 | **50 passed / 23 failed**（逐条"功能缺失"，如 `test_role_camera_ctrl_real_scenario_is_8_not_4: AssertionError: 单继承链 ⇒ 4`、`test_virtual_bases_override_…: AssertionError: ['VB2']`） |
| 绿 | 同上 | **73 passed / 0 failed / 0 skipped**（含端到端裁判全量，11 s） |

**变异检验**（6 个变异体，全部被杀 ⇒ 新测试有判别力，非事后补测）：

| 变异体 | 结果 | 被杀测试（节选） |
|---|---|---|
| M1 虚基区域退回"只看直接虚基" | KILLED (8) | `test_indirect_virtual_base_region_covers_whole_closure` · `…_never_yields_active_offset_assert` · `…_is_transitive` |
| M2 `--virtual-bases` 退回求交 | KILLED (3) | `test_virtual_bases_override_adds_missing_base_…` · `…_unknown_name_is_added_and_warned` |
| M3 一致性档失效 | KILLED (2) | `test_consistency_only_tier_activates_size_and_offset` · `…_leaves_shape_rules_untouched` |
| M4 关掉外部（gb*）兜底 | KILLED (3) | `test_external_prefix_class_shape_is_suspect` · `test_real_data_gb_classes_have_no_active_assertions` |
| M5 载体判据退回 `methods` | KILLED (4) | `test_pmf_carrier_is_decided_by_vtables_not_methods` · **`test_real_emitted_asserts_have_no_false_kill`** |
| M6 关掉发射头名单兜底 | KILLED (3) | `test_declared_classes_gate_marks_undeclared_shape_suspect` · `test_declared_gate_applies_to_closure_too` |

**假杀复现（评审发现项的独立复核）**：把 C-3 判据临时退回 R=0（`elif False`）⇒ 裁判立刻报

```
编译: total=140 pass=131 false_kill=1 …
  FALSE-KILL RoleCameraCtrl: sizeof(void (RoleCameraCtrl::*)()) == 4
    _a_RoleCameraCtrl_pmf.cpp(3) : error C2118: negative subscript or subscript is too large
```

⇒ 与评审"1 假杀"完全对上；修复后同一命令 **0 假杀**。

## R=1.3 端到端裁判逐字输出（修复后）

```sh
$ python3 data/status/_layout_assert_probe_20260925/verify_emitted_asserts.py --jobs 6
=== 端到端裁判（真实生效断言 × 真实发射头，MSVC6）===
生成口径: total=10918 active=140 commented=10778 consistency-only=0
编译: total=140 pass=132 false_kill=0 unreliable=0 assert_error=0 header_error=8
未编译: no_header=0 spec_header=0 by_root={'pal3/src': 140}
  HEADER-ERROR CCBParabolaWindow (Combat/CCBParabolaWindow.h): ['C2555@32']
  HEADER-ERROR CEffTrackCustomShape (Misc/CEffTrackCustomShape.h): ['C2584@7']
  HEADER-ERROR CEffTrackCylinder / CEffTrackGrid / CEffTrackModel / CEffTrackQuad / CEffTrackSParticle（同 C2584）
  HEADER-ERROR PlayerAtt (Misc/PlayerAtt.h): ['C2061@91']
=== ALL CHECKS PASSED ===
$ python3 .../verify_emitted_asserts.py --self-test
SELF-TEST OK: pass=1 false_kill=1
```

8 个"骑在有错头上"的类 = 评审独立复算的同一集合（6 个 `CEffTrack*` = I-1，按裁定转注解修复）；
分类按**行号**区分"断言行"与"头文件自身"，头本身编不过时归 `unreliable`（不判生成器）。

**真实的 176 → 140 生效断言**（评审给出的 176 中，删除的 36 条 = 23 个 gb* + 13 个闭包含 gb* 基类者；
后 13 条按新规则**今天并不会假杀**（无 gating 全量编译实测），属"规则不可证 ⇒ 降级"的保险，
不是修 bug —— 见 R=1.4）。同时新增 `--declared-classes`（发射头名单）兜底：名单外的类
（含闭包内出现者）⇒ SUSPECT；本轮实测该兜底在**完整名单**下额外覆盖代价 **0 条**。

## R=1.4 `consistency-only`（I-2）在真实数据上的实测（⚠️ 给 Task 8）

`--untrusted-policy consistency-only` 在默认口径外新增第 4 档；真实数据：

```
wrote /tmp/_la_consistency.h | total=10918 active=8986 commented=1932 skipped=2
      (trusted=140 same-source=0 suspect=1932)
by_trust = {'consistency-only': 8846, 'trusted': 140, 'suspect': 1932}
```

抽样 14 个成员最多的类（1841 条断言）逐条真机编译：

```
total=1841 pass=1706 false_kill=64 unreliable=0 assert_error=71 header_error=0
  FALSE-KILL CCBRoleState sizeof(CCBRoleState) == 22224
  FALSE-KILL CCBRoleState offsetof(CCBRoleState, m_byteFlags) == 7676
  ASSERT-ERR CCBRoleState offsetof(CCBRoleState, m_sCombatDialog) == 0   ['C2039@3']
```

⇒ **该档是"漂移探测器"，不是可常开的一致性闸**：它立刻暴露三类既有漂移
（①注解把基类成员摊平进本类、发射头改走继承 ⇒ C2039；②基类 `sizeof`/vfptr 模型与发射头
不一致 ⇒ 成员整体位移 C2118；③同源常量本就不保证与声明一致 E-2）。
**低成本启用路径：按类试运行**（`--only <类> --untrusted-policy consistency-only`），
不要一次性全开 —— 否则 `_layout_asserts.h` 被 include 时会直接编译失败。

## R=1.5 病灶层检查（动手前的三个问题）

1. **病灶在哪一层**：全在**生成器自身的判据层**（`tools/layout_assert_gen.py`），不碰管线。
   真值源仍是**真机编译器**：C-3 的规则由 `pmf_intro.cpp`（`/FAs` 读编译器算出的常量）确证，
   C-1 由 `ivb.cpp` 逐字 C2057+C2466 确证。
2. **消费者实际读什么**：断言消费者是 codegen 发射头 → `_layout_asserts.h`；生成器的"载体"
   判据必须与**发射头里的 virtual** 同源 —— 实测 `emit_headers.py:2460` 用注解 `vtables` 的槽位
   发射 `virtual`（`PalScriptWaitObj.h` 只有 `methods` ⇒ 0 virtual）⇒ 判据改用 `vtables` 有直接证据；
   外部类（`gb*`）的声明在 `include/gbengine/*` 手写 spec 头（`gbRefObject` 自带 `virtual ~`）
   ⇒ 与注解不同源 ⇒ 必须降级。
3. **报错还缺什么信息**：C2118 只给行号 ⇒ 裁判按行号区分"断言行/头文件自身"，
   并对"头本身编不过"单列 `unreliable`（避免把连锁噪声误判成假杀）。

## R=1.6 顾虑（交上层 / 影响 Task 8）

1. **`declared_classes` 是保险而非修复**：真实数据上它额外代价 0 条，但语义是"声明必须由注解
   发射"。Task 8 若从 `pal3/src/**` 反查名单，请**带上同名 `X.h` shim**（模板具体化的
   `typedef` 头，实测 26 个 `CTaskTpl_*` 类，其具体化类体同样由注解发射 ⇒ 与注解可比）。
2. **闭包 gb* 降级（13 条）是"不可证"而非"已证错"**：不加 gating 全量编译实测它们今天都能过；
   但 `gbRefObject` 这类 spec 头确实会自行引入 virtual（gbTexture 实测 4 vs 规则 8）⇒
   保留降级；若 Task 8 能把 spec 头的 `virtual` 也纳入输入，这 13 条可恢复。
3. **8 个发射头自身编不过**（`CEffTrack*`×6 / `CCBParabolaWindow` / `PlayerAtt`）：其中 6 个是
   I-1（重复间接基，已裁定转注解修复），另 2 个（C2555 覆盖返回类型 / `RoleAtt.h:91` C2061）
   需另立任务；在这些头修好前，这 8 条形状断言无法被端到端判定（裁判归 `header_error`）。
4. **I-2 档的真实漂移密度**：抽样 1841 条中 64 假杀 + 71 C2039（3.5%/3.9%）⇒ 若 Task 8 全量启用，
   会先撞 C1003 截断与海量 C2118；建议按类白名单推进。
5. **`--virtual-bases` 只有测试覆盖、真实数据仍无虚基标记**（R=0 顾虑 2 不变）：C-2 修好后，
   回填入口可用，但"PAL3 是否真有虚基类"仍需 Task 8 用 vbtable 反查。
6. 本环境 pytest 恒崩（R=0 记录一致）⇒ 73 条以文件内独立运行器验证；CI 上可直接收集。
