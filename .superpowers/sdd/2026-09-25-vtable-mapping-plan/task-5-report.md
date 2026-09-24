# Task 5 交付报告：声明校验（棘轮制）

- **状态**：**DONE_WITH_CONCERNS**
- **交付**：`tools/vtable_decl_check.py`（校验器 + 棘轮 + CLI，1392 行）·
  `tests/test_vtable_decl_check.py`（**81 测**）
- **一行测试摘要**：**新 81 passed / 0 failed** · 前序无回退（**35 / 38 / 68 / 46**，四次运行均为该值）·
  真实数据端到端跑通（78 类 / 841 槽，flat `slot_health 0.588585`）·
  真实生成头变异 3 条（换址/删声明）全部报警且棘轮阻塞
- ⚠️ **并发说明（不是我的变更）**：本任务收尾时 `tests/test_layout_assert_gen.py` 被**另一实现者**
  并发编辑（`git status` 显示 ` M`，mtime 23:14:50；新测试期望 `ClassLayout(has_vtables=…, has_methods=…)`
  而 `tools/layout_assert_gen.py`（mtime 22:30）尚未同步）⇒ 该套测试在我收尾的**最后一次**运行里
  为 `9 passed / 64 failed`。**本任务不曾触碰这两个文件**；我四次运行（动手前 / 实现中 / 实现后）
  均得 **46 passed / 0 failed**，见 §6.1 与 §10。
- **提交**：`（见文末「提交」）` —— `.superpowers/sdd/` 被 `.gitignore` 排除，本报告只落盘不入库

> **无子代理**：本任务全程未分发任何子代理（遵守"无子代理契约"）。
> **未触碰管线 / 未触碰他人文件**：只新增上述两个文件；**未**运行 `pipeline/cli.py loop|apply|export|codegen`，
> **未**修改 `vtable_sig_infer.py` / `vtable_slot_classifier.py` / `vtable_slot_order.py` /
> `layout_assert_gen.py` / `vtable_verify.py` / `stage3_cleanup.py`。
> 对 `data/annotations/**` **只读**：`main()` 硬拒 `--baseline`/`--json` 落在该目录（实测 exit 2）。

---

## 1. 需求对照

| 需求（简报/规格 §4.5） | 实现 | 证据 |
|---|---|---|
| 校验项 1 **槽数数**：声明数量 == `vtables[].slots` 数量（按 view 对，MI 多表各自校验） | `check_class()` 逐 view 算 `n_decl_addr + n_decl_addrless` vs `n_slots`；`_match_views()` 按 标签→槽数→序号 配对，配不上的表记 `view_unmatched`（0 分，不静默放过） | `test_count_check_*` ×4；MI 用例 2 表各自计数 |
| 校验项 2 **槽序**：用 Task 1 正向规则从声明生成预期槽序，逐槽对比 | `compute_slot_order()`（flat）/**`compute_class_views()`（chain）** → 逐槽位置对齐 | `test_order_*` ×8；真实数据 `CEffectSystem` 实测差异被报出 |
| 校验项 3 **签名**：Task 3 候选 vs 声明（**等价类**维度） | `signature_verdict()`：arity / 返回宽度 / 参数等价类 / 变参 / 约定 五维；B/C 带证据即 `SIG_OK` | `test_signature_*` ×15 |
| **棘轮制门禁**：health 只升不降（升⇒放行+更新基线；平⇒放行；降⇒阻塞） | `ratchet_decide()` → `RatchetDecision(up/same/down/new/missing/unmeasured)`；`build_baseline()` | `test_ratchet_*` ×11 |
| **禁止硬门禁**（v1/v2 两次死锁） | 无任何阈值/比例参数；0 已验证也放行 | `test_ratchet_zero_verified_does_not_block_no_hard_gate`（并断言 `ratchet_decide` 无 `threshold` 参数） |
| TDD（先测试红 → 实现 → 绿） | 红：`ModuleNotFoundError: No module named 'vtable_decl_check'` ⇒ 实现 → 81/0 | §6 |
| Ruling 1–5 各 ≥1 正/负例 | 见 §5 对照表（共 15 条专门用例 + 真实数据变异 3 条） | — |
| 负向/变异测试（改槽序/槽数/签名必须报警） | 合成变异 6 条 + **真实生成头变异 3 条** | §6.2 |
| 交付报告 | 本文件 | — |

---

## 2. 交付 API（供 Task 6/7/8 消费）

```python
from vtable_decl_check import (parse_decl_text, load_decl_dir, load_structs_dir, load_pending,
                               norm_addr_key, build_hierarchy, to_virtual_decls,
                               decl_slot_order_kind, decl_arity, cpp_type_param_class,
                               cpp_return_kind, signature_verdict,
                               check_class, check_all, build_baseline, ratchet_decide,
                               render_report, report_to_dict, main)

decls   = load_decl_dir('pal3/src')                       # {类名: ClassDecls(bases, decls[DeclSpec])}
structs = load_structs_dir('data/annotations/structs')    # {类名: [BinaryView(addr, base, slot_addrs)]}
pending = load_pending('methods_pending.json')            # {归一地址键: record}（Ruling 3）

res = check_all(decls, structs, pending=pending, model='flat')   # CheckResult
res.classes['CUtil'].slot_health      # 棘轮主分量（= 规格里的 vtable_health[class]）
res.classes['CUtil'].count_health     # 槽数分量（防"多/少声明、无地址声明"）
res.classes['CUtil'].sig_health       # 签名分量（无证据 ⇒ None，不进分母）
res.views['CUtil'][0].slots           # 逐槽判定（order / signature / grade / features / waived / notes）
res.findings                          # 人读发现项（可归因：槽数/槽序/签名/view_unmatched/无地址声明）
res.stats                             # 全局分量 + 体积统计 + model

d = ratchet_decide(baseline_dict, build_baseline(res))
d.state          # 'pass' | 'improved' | 'blocked'
d.components     # [(class, metric, base, current, 'up'|'same'|'down'|'new'|'missing')]
d.updated        # 上升且未阻塞时的新基线（消费方落盘）
d.comparison     # 'ok' | 'model_changed'（模型切换 ⇒ 本次不做对比）
```

CLI：

```sh
python3 tools/vtable_decl_check.py --decls pal3/src --structs data/annotations/structs \
    --pending /tmp/pending.json --model flat --baseline /tmp/base.json [--write-baseline] \
    [--json /tmp/report.json] [-q]
# 退出码 0 放行 / 1 棘轮阻塞 / 2 输入·写入错误
```

---

## 3. 三类校验项的实现口径（含为什么）

### 3.1 声明侧的证据来源：**codegen 生成头**

真实生成头（`pal3/src/**/*.h`）里的 virtual 声明带地址尾注释，**天然就是"声明 → 槽地址"的映射**：

```cpp
    virtual void slot_0(); // 0x445e70
    virtual int RenderFrame(); // 0x00523670
    virtual ~CGameData() {}          // ← 注入的虚析构：无地址注释
```

解析实测：**948 条 `virtual` 行 → 948 条解析成功（0 漏、0 可疑）**，79 个类、含 `const`/变参/
指针返回/内联析构等形态。`~C()` 记 `kind=deleting_dtor`，`= 0` 记 `purecall`，其余 `fn`（**均 Task 2 词面**）。

### 3.2 两类顺序模型（默认 `flat`，理由是**实测**不是偏好）

| 模型 | 预期槽序 | 真实数据（78 类 / 841 槽） | 说明 |
|---|---|---|---|
| `flat`（默认） | `compute_slot_order([], 本类声明)` | `slot_health 0.588585` · `order_ok 495` · 全对 45 · 全错 10 | 发射器把**整张表**（含继承槽）都写进本类头 ⇒ 声明表即完整槽表 |
| `chain` | `compute_class_views(hierarchy, cls)` | `slot_health 0.305589` · `order_ok 257` · 全对 18 · 全错 43 | MI 逐视图（合成夹具已验证 5/5）；真实数据受补位命名缺口限制（§9 顾虑 2） |

**注意（重要、写给复核者）**：`flat` 之下"声明序 → 预期序"并非同义反复 —— 它把 Task 1 的
**编译器规则**（同名组内逆序、合成槽单槽组）作用在声明序上，而发射器是按**二进制槽序**写声明的。
两者在**同名重载组**上必然分歧，这正是真实数据里 `CEffectSystem`（1/9）被报出的原因：

```
声明：slot_0@0x4C5D50, Reset@0x4C6260, slot_1@0x4C5D80, slot_2@0x4C5DB0, … , UpdateEffectState@0x4C6030
二进制：0x4C5D50, 0x4C5D80, 0x4C5DB0, 0x4C5DE0, 0x4C5E70, 0x4C5E80, 0x4C5E20, 0x4C6030, 0x4C6260
⇒ Reset 被发射器排到槽 1，真实表里在**最后**（我们的校验报 8 个位置错位）✓
```

### 3.3 槽序对比的三种判定（位置对齐，不是贪心查找）

* `ok`：预期序列该位置的地址 == 二进制该槽地址
* `alias`：该地址**之前已出现过**且已被声明覆盖 ⇒ 二进制同一函数占多槽（**算已验证**，留痕"别名槽"）
* `mismatch`：该地址被声明了，但不在这个位置（纯顺序问题）
* `undeclared`：该地址**没有任何** virtual 声明覆盖（发射器不会为它生成声明 ⇒ 编译出的表会短）

> 早先版本用"贪心查找"（找到就消费一个位置），被 `test_order_uses_task1_group_reversal_for_overloads`
> 抓住：`[o(),o(int)]` 的二进制逆序只报了 1 处错位而不是 2 处。这是**测试先于实现定死语义**的价值。

### 3.4 签名对比：等价类 5 维 + features 驱动豁免（Ruling 1/2）

| 维度 | 判据 | 豁免条件（读 `features`，Ruling 2） |
|---|---|---|
| 调用约定 | 仅 **A 级 ∧ 非 `cc_provisional` ∧ 非 `this_on_stack` ∧ 非变参** 才算硬矛盾 | `this_on_stack` |
| 变参 | `variadic` 必须一致 | — |
| 参数个数 | `arity` 精确相等；下界型则 `声明 ≥ arity` | `arity_is_lower_bound` / `hidden_param_suspicion` ⇒ 放宽为下界；`sret_ambiguous` ⇒ 允许 ±1 |
| 返回宽度 | 声明返回类型 → Task 3 词面（指针/`BOOL`→`i32`；按值结构体⇒**不判**）后必须相等 | `sret_ambiguous`（判不出）；`sret`（已判定）**不豁免** |
| 参数等价类 | 声明参数类 ∈ 候选 `class_candidates`（或与之 `param_class_equiv`） | `sret_ambiguous` / `sret`（整体可能错位一位） |

**计分**：`SIG_OK`（至少 1 个判定维度相符且 0 矛盾）/ `SIG_SYNTHETIC_OK`（合成槽：Task 3
`skipped=True` 或声明 kind 为合成）/ `SIG_CONTRADICTION` 进 `sig_health` 分母；
`SIG_UNCHECKED`（无证据）、`SIG_WEAK`（有候选但什么都没判定）**不进分母** —— 这保证
"新证据出现"只能抬高或持平 `sig_health`，不会倒打一耙（棘轮单调）。

---

## 4. 棘轮制（核心）

```
vtable_health[class] = 已验证槽数 / 总槽数        ← slot_health（规格口径）
棘轮：升 ⇒ 放行 + 更新基线 · 平 ⇒ 放行 · 降 ⇒ 阻塞
```

**为什么是三个分量**：单一标量会让棘轮留洞 —— 例如"多声明一个虚函数"完全不改槽序
（`slot_health` 不变）⇒ 只用一个分量就察觉不到。故拆成三个**各自单调**的分量，任一**下降**即阻塞：

| 分量 | 定义 | 防的倒退 | 测试 |
|---|---|---|---|
| `slot_health` | 槽序命中（含别名槽）/ 总槽数 | 槽序错位、槽位无声明、view 未匹配 | `test_ratchet_decrease_blocks` |
| `count_health` | 命中声明数 / (声明数 + **无地址声明数** + 未覆盖槽数) | 多声明、少声明、`virtual ~C() {}` 这类不可定位声明 | `test_count_check_*` |
| `sig_health` | 签名无矛盾 / 有签名证据（无证据 ⇒ `None`） | 声明与二进制序言/调用序列矛盾 | `test_ratchet_signature_health_decrease_blocks_without_slot_change` |

其他门的语义（都有测试）：

* 基线有、当前没有的类 ⇒ `missing` ⇒ **阻塞**（整类验证面消失同样是倒退）
* 当前新增的类 ⇒ `new` ⇒ 不算倒退
* 基线未测（`None`）而当前有值 ⇒ `unmeasured` ⇒ **不阻塞**（新证据不得倒打一耙）
* **模型切换**（flat↔chain）⇒ `comparison='model_changed'` ⇒ 不做对比、也不阻塞，
  要求显式重建基线（否则"假绿"或"假红"必居其一）
* **无阈值**：`ratchet_decide` 签名里没有任何 threshold 参数，0 已验证只要不降就放行
  （v2 规格曾把不等号写反："未解析 < 阈值 ⇒ 阻塞" ⇒ 0 未解析反而阻塞 ✗）

CLI 的 `--write-baseline` 是**显式**开关（规格的"上升⇒更新基线"由 `ratchet_decide().updated`
提供）：本仓常有多个实现者并行，默认不落盘以免争用同一基线文件。

---

## 5. Ruling 1–5 对照（每条都有正例与反例）

| Ruling | 实现口径 | 正例 | 反例 |
|---|---|---|---|
| 1 棘轮接受 **B/C 带证据** | 只要被判定的维度无矛盾即 `SIG_OK`，不要求 A | `test_ruling1_grade_b_with_evidence_accepted` · `..._grade_c_...` | `test_signature_mutation_extra_param_is_contradiction`（A 级下改签名必报警） |
| 2 必须读 `features` 区分 `sret_ambiguous` / `hidden_param_suspicion` | `_waived_for()`：前者豁免 return/arity/params（"判不出"），后者只把 arity 放宽为下界（"有隐藏参数嫌疑"） | `test_ruling2_sret_ambiguous_waives_return_dimension` · `..._hidden_param_suspicion_waives_exact_arity` · `..._two_features_are_distinguishable_not_grade_only`（同 grade=B，`waived` 必须不同） | `test_ruling2_hidden_param_suspicion_does_not_accept_arity_below` · `test_ruling2_determined_sret_return_is_checked_not_waived`（已判定的 `sret` 不豁免 return，声明 void 仍矛盾） |
| 3 键归一小写 | `norm_addr_key()` 一律 `'0x%08x'`；声明地址→键、pending 键都过它 | `test_ruling3_lowercase_pending_key_is_found` · `test_ruling3_end_to_end_mixed_case_pending_keys` | `test_ruling3_naive_uppercase_lookup_would_miss`（不归一时 0.94% 键漏） |
| 4 词面统一经适配器 | `decl_slot_order_kind()`：`normalize_kind()` → 合成类走 `slot_order_kind()`，`fn`/`purecall` → `KIND_FUNC` | `test_ruling4_fn_word_survives_adapter_and_is_not_synthetic` | `test_ruling4_naive_pass_through_would_misorder`（`'fn'` 直传 Task 1 ⇒ 全被当合成槽 ⇒ 同名组逆序消失） |
| 5 基准是编译产物（独立于 methods 表） | 只读 `vtables[].slots`（IDB 直读 `.rdata`）+ 生成头 + Task 3 旁路；**从不读 `methods`** | `test_ruling5_methods_table_not_consulted`（把 methods 改成与 vtable 矛盾，判定逐字不变） | `test_ruling5_checker_never_reads_struct_methods_key`（源码静态守卫：无 `['methods']` 字样，签名证据入口唯一 = `methods_pending`） |

> **词面细节补充**：`purecall` **不**当作 Task 1 的合成槽 —— 纯虚函数在声明级仍是普通虚函数
> （参与同名分组），只是槽内容指向 CRT stub。`_SYNTHETIC_DECL_KINDS` 只含
> `deleting_dtor`/`adjustor_*`/`composite`。这条有专门注释与解析测试覆盖。

---

## 6. TDD 记录与判别力

### 6.1 红 → 绿

```
$ python3 tests/test_vtable_decl_check.py
Traceback (most recent call last):
  File ".../tests/test_vtable_decl_check.py", line 43, in <module>
    from vtable_decl_check import (
ModuleNotFoundError: No module named 'vtable_decl_check'          # ← 红（全部 81 条不可收集）
```

实现过程（每轮都是**测试先抓出缺陷**）：

| 轮 | 结果 | 抓出的问题 |
|---|---|---|
| 1 | 68 passed / **6 failed** | ① 贪心对齐漏报错位（§3.3 那条 bug）② MI 用例缺基类地址索引 ③ 测试自身 `hs` 断言写错 |
| 2 | 72 / 3 | 位置对齐与 `undeclared` 判定优先级 |
| 3 | 73 / 2 | flat 模型对 MI 的**已知限度**（改为断言"部分命中 + 次表未匹配"） |
| 4 | **74 / 0** | 绿 |
| 5 | 76 / 0 | 补 Ruling 2「已判定 sret 不豁免 return」+ 弱/矛盾混合候选的排序回归守卫 |
| 6 | 79 / 1 → **80 / 0** | 真实头变异断言过严（换址只损伤 2 个位置 ⇒ 改为局部化断言） |
| 7 | **81 / 0** | 补模型切换可比性用例 |

### 6.2 变异/负向测试（判别力证据）

**合成夹具**（改一处，断言必须报警）：

| 变异 | 期望 | 用例 |
|---|---|---|
| 对调两条声明的地址 | 两槽 `mismatch` · `slot_health 0` · 棘轮阻塞 | `test_order_mutation_swap_decl_addresses_is_reported` |
| 二进制槽序逆序（同名重载组） | 两槽 `mismatch` | `test_order_uses_task1_group_reversal_for_overloads` |
| 多声明一个虚函数 | `count_ok=False` · `count_health<1` | `test_count_check_extra_decl_reported` |
| 少声明一个虚函数 | 该槽 `undeclared` · `slot_health 0.5` | `test_count_check_missing_decl_reported` |
| 声明多一个参数（A 级候选） | `arity_mismatch` | `test_signature_mutation_extra_param_is_contradiction` |
| 参数类矛盾 / 返回矛盾 / 变参矛盾 / 约定矛盾 | 各自 detail | `test_signature_*_contradiction*` ×4 |
| 只改次视图槽序（MI） | 主视图 3 槽仍 ok、次视图 2 槽 `mismatch` | `test_order_mi_secondary_view_mutation_blocks_that_view_only` |

**真实数据变异**（`TestRealDataMutation`：真实 `CUtil.h` + 真实二进制表做基线）：

| 变异 | 结果 |
|---|---|
| 原样 | `slot_health 1.0` · `count_ok=True` · 7 槽 |
| 对调前两条声明的**真实地址注释** | `slot_health 5/7=0.714` · `n_order_ok=5` · **棘轮 blocked** |
| 删掉 `WriteLog` 那一行声明 | `slot_health<1` · finding 含"无声明" · **棘轮 blocked** |

---

## 7. 真实数据端到端

```sh
python3 tools/vtable_decl_check.py --decls pal3/src --structs data/annotations/structs \
    --baseline /tmp/base.json --write-baseline   # rc=0（首次运行 → 写基线）
python3 tools/vtable_decl_check.py ... --baseline /tmp/base.json   # rc=0（持平 → 放行）
# 删一条声明后再跑 ⇒ rc=1（BLOCKED）
python3 tools/vtable_decl_check.py ... --baseline data/annotations/x.json --write-baseline  # rc=2（拒写注解目录）
```

| 指标 | flat（默认） | chain | 说明 |
|---|---|---|---|
| 类 / 槽 / view / 未匹配 view | 78 / **841** / 92 / 14 | 同 | 槽总数与 `data/status/vtable_baseline.json` 的 `total_slots=841` **一致** |
| `slot_health`（全局） | **0.588585**（495/841） | 0.305589（257/841） | 逐类均值 0.6969；全对 45 类、全错 10 类 |
| `count_health` / `count_ok` 类 | 0.642 / 22 | 0.315738 / 11 | |
| 无地址声明 | 30 条 | 51 条 | 注入虚析构（如 `virtual ~CGameData() {}`） |
| `sig_health` | `N/A`（仓库无 pending 产物） | `N/A` | 用合成 pending 实测：`sig_checked 46`、`sig_ok 2`、矛盾 44（见下） |
| findings | 316 | 586 | 可归因到 类+view+槽+地址 |

**两个真实样本**（写进报告供后续归因）：

* `CUtil`：7/7 全对，`count_ok=True`（声明序 = 二进制序，逐槽地址一致）✓
* `CGameData`：`slot_health 1.0` 但 `count_health 0.875`、`count_ok=False` —— 因为头里同时有
  `virtual ~CGameData() {}`（无地址）与 `virtual void _scalar_dtor(); // 0x0044F030`，
  共 8 条声明对 7 槽 ⇒ **槽数项如实报警**（这正是一个需要 IDA 归因的真实候选：注入的虚析构
  与 `_scalar_dtor` 声明重复表达同一个 deleting-dtor 槽）
* Ruling 3 真实链路：把 Task 3 口径的**大写**键 pending 喂给 CLI（`0x00445E70` 等），
  `sig_checked=46` 命中（若键不归一则为 0）✓

---

## 8. 病灶层检查（动手前的三个问题）

1. **病灶在哪一层？** 声明校验是**发射器层 + 编译器布局规则**之间的关卡：声明由
   `pipeline/gen/stages/emit_headers.py` 按**二进制槽序**写出（`_method_sort_key`/`_vtable_addr_order`），
   而编译器按 C++ 规则（同名组逆序等）重新排 §2.2 的槽序。偏差可能来自三处：发射器排序、
   注解 `vtables[]` 不完整、Task 1 规则模型 —— 本工具只**定位并归因**，不改任何一层。
2. **消费者实际读的是哪个文件/哪份声明？** 声明侧读 `pal3/src/**/*.h` 的 `virtual ...; // 0xADDR`
   （已实测 948/948 解析）；基线侧读 `data/annotations/structs/*.json` 的 **`vtables[].slots[].addr`**
   （**不**读 `methods`）；签名侧读 Task 3 的 `methods_pending`（大写键，归一小写后消费）。
3. **报错还缺什么信息？** `vtable_mapper.py`（旧硬门禁）只说"槽 N 的地址不在 methods 表"，**不给**
   槽序/槽数/签名的分量与基线对比，也无法区分"少声明/顺序错/签名矛盾"。本工具把每条 finding 做成
   `类 + view + 槽下标 + 地址 + 判定 detail(+grade/features/waived)`，并把"是否比基线退步"单独报出。

---

## 9. 顾虑（需上层裁定 / 影响 Task 6–8）

1. **`flat` 是默认、`chain` 在真实数据上不可用（重要）** —— `chain` 偏低的原因**已定位**：
   发射器给补位槽起的名字按**本表**槽下标（`slot_N`），基类同名槽的 `slot_N` 与之不同 ⇒
   Task 1 `match_key` 认不出"同一槽的继承"，把继承段当新增段重复计数（`CCBControlWindow`
   chain 下 51 条声明 vs 8 槽）。⇒ **建议**：MI 逐视图校验要真正可用，需先让发射器补位名
   与基类槽对齐（或按槽地址回填），此属发射器/Task 6 范围。本任务对此只做**显式记账**
   （`view_unmatched` + 模型切换不可比），不静默放过。
2. **注解 `vtables[]` 不完备，且"多视图"字段语义混乱** —— 80 个类有 `vtables`，但
   `UIWnd.json` 的 3 个"view"实测是**3 个不同类**的同形表（view1 里是 `CCBProtectWindow` 的地址）；
   10 个多视图类里 `base` 字段 56/94 有值。MI 的**次表**（`??_7X@@6B<次基>@@@`）大多根本没记。
   ⇒ 本工具因此把"未匹配的二进制表"记为未验证（保守、只升不降），但**完整性缺口**应由
   annotation 完备性校验（Task 8 范围）解决。
3. **`--write-baseline` 是显式开关（规格语义的偏离，出于并发安全）** —— 规格写"上升⇒更新基线"，
   本工具由 `ratchet_decide().updated` 提供该语义，但 CLI **默认不落盘**（本仓多个实现者并行，
   同一基线文件会被争用）。若上层要求自动落盘，改一行即可（`args.write_baseline` 默认值）。
4. **本任务不做管线集成** —— 未把校验接进 `codegen`（Task 8 端到端范围），也未产出
   `data/status/vtable_decl_health.json` 基线文件（应由集成方在**完整一次管线运行**后落盘，
   否则基线取自陈旧生成头）。**建议 Task 8**：先跑 codegen 再 `--write-baseline` 作为当日基线。
5. **签名分量当前恒 `None`** —— 仓库里没有全量 `methods_pending` 产物（Task 3 只产出旁路到
   `--out`）。因此真实数据的 `sig_health` 未生效，只在合成 pending（含 Task 3 口径大写键）
   上验证过链路。**不影响棘轮单调性**（无证据不进分母）。
6. **`sig_health` 的"有证据"口径是保守的** —— 只有 arity/返回宽度/参数类/变参/约定中被**判定**
   的维度才计入；全部 `RET_UNKNOWN`+`arity=None` 的弱候选记 `SIG_WEAK`（不进分母）。
   若上层希望"有候选即算已验证"，需改 `signature_verdict` 一处判断（但会降低判别力）。
7. **`count_health` 的分母口径是自定义的**（声明数 + 无地址声明数 + 未覆盖槽数）——
   规格只说"声明数量 == slots 数量"（我们保留了 `count_ok` 布尔）。自定义分母是为了让
   **"多一个声明"也能被棘轮拦住**；若上层要求与规格逐字一致，请裁定改为布尔。
8. **`flat` 的顺序校验对"发射器已按二进制序写出"这一点是部分同义反复** —— 它拦得住
   发射器排序回归与编译器同名组逆序效应，但**不能**替代 Task 6（`.obj` 编译产物 vs `.rdata`
   逐槽对比）作为 vtable 数据的最终裁判。本模块定位为**棘轮式回归闸**，符合规格 §4.5/§7。

---

## 10. 证据链自检

* 工具对 `data/annotations/**` **只读**（`main()` 硬拒 `--baseline`/`--json` 落在该目录，实测 exit 2）；
  不写 IDB；不发子代理；未跑任何管线命令。
* **Ruling 5 静态守卫**：源码里不存在 `['methods']`/`["methods"]` 取键；签名证据入口唯一 =
  `methods_pending`（`test_ruling5_checker_never_reads_struct_methods_key`）。
* 真实数据锚点是**计数级**的：78 类 / 841 槽（与 `data/status/vtable_baseline.json` 的
  `total_slots=841` 相符）；`CEffectSystem` 的错位是二进制表里的真实地址序，不是构造出来的。
* 真实数据变异测试用**真实生成头 + 真实二进制表**（不是合成字符串），证明报警不是夹具自证。
* 全部 5 套测试同跑（收尾前）：**35 / 38 / 68 / 46 / 81 passed，0 failed**。
  收尾时第 4 套因**另一实现者并发编辑其测试文件**而变红（见开头「并发说明」）——
  与本次交付的两个文件无交集（`git status` 只显示 ` M tests/test_layout_assert_gen.py`，
  `tools/layout_assert_gen.py` 未被改动）。

---

## 附录：复现

```sh
cd /home/peng/workspace/PAL3Decomp
python3 tests/test_vtable_decl_check.py                     # 81 passed / 0 failed
python3 tests/test_vtable_slot_order.py                    # 35
python3 tests/test_vtable_slot_classifier.py               # 38
python3 tests/test_vtable_sig_infer.py                     # 68
python3 tests/test_layout_assert_gen.py                    # 46

# 真实数据（只读；不碰 IDB / 管线）
python3 tools/vtable_decl_check.py --decls pal3/src --structs data/annotations/structs \
    --baseline /tmp/t5_base.json --write-baseline -q          # rc=0，写基线
python3 tools/vtable_decl_check.py --decls pal3/src --structs data/annotations/structs \
    --baseline /tmp/t5_base.json -q                            # rc=0（持平）
python3 tools/vtable_decl_check.py --decls pal3/src --structs data/annotations/structs \
    --model chain -q                                           # rc=0（诊断用；见 §9 顾虑 1）
```

## 提交

- 提交：**`50ecae6f4`**（`feat(vtable): Task5 声明校验（棘轮制）—— 槽数/槽序/签名三分量 + 只升不降门禁`）
- 变更范围（`git show --name-only` 逐字核实）：`tools/vtable_decl_check.py`（新增，1408 行）·
  `tests/test_vtable_decl_check.py`（新增，1090 行）—— **只有这两个文件**
- 前序测试无回退：35 / 38 / 68 / 46（layout_assert 的收尾变红属**他人并发编辑**，见开头「并发说明」）
---

# R=1 修复轮：门禁语义洞（4 Important + 2 Minor）

- **状态**：**DONE_WITH_CONCERNS**
- **范围**（严格）：只改 `tools/vtable_decl_check.py` + `tests/test_vtable_decl_check.py`；
  **未**运行 `pipeline/cli.py loop|apply|export|codegen`；**未**触碰他人文件（Task 4/6/7 并发修复中）。
- **一行测试摘要**：**87 passed / 0 failed**（原 81 + 新 6）· 前序无回退 **35 / 38 / 68** ·
  真实数据端到端 4 步验证通过（缩水基线**写不进去**）。

## 1. 修复项对照

| # | 等级 | 洞 | 修法 | 测试 |
|---|---|---|---|---|
| Q1 | Important | 棘轮只比**比值**（`_METRICS` 三个 health），`slots`/`count_denom`/`slots_total` 完全不参与对比 ⇒ ①删未声明槽 `slot_health 0.5→1.0` ⇒ 判 `improved` **并回写基线**；②同时删声明与其槽（3 槽→1 槽）⇒ 三分量全 `same` ⇒ **放行** | 新增**第 4 类单调分量** `_SURFACE_METRICS = ('slots','count_denom')` 并入 `_RATCHET_METRICS`（"验证面不得缩小"，与 `missing ⇒ 阻塞` 同语义）；`down` 时给专门 note。另 `improved = improved and not blocked`（阻塞优先，被阻塞的运行不得同时报"改善"） | `test_ratchet_undeclared_slot_removal_is_not_improved` · `test_ratchet_declaration_and_slot_removal_does_not_pass`（**红→绿**）|
| Q2 | Important | `--write-baseline` 无 `--baseline` ⇒ exit 0、不落盘、无告警 ⇒ 无基线 ⇒ `decision is None` ⇒ **一切运行恒 exit 0**（门禁永久静默关闭） | `main()` 首段显式校验：缺 `--baseline` ⇒ stderr 报错 + **rc=2** | `TestCli.test_cli_write_baseline_without_baseline_is_usage_error` |
| Q3 | Important | `if bv is None or cv is None: status='unmeasured'`（不阻塞）把**两个方向**合并：base `sig_health=1.0` → 当前 `None`（漏传 `--pending`）⇒ 不阻塞（**证据源丢失**被当新证据） | 拆成两条单向分支：`cv is None`（base 有值）⇒ `down` + 阻塞 + "证据源丢失" note；`bv is None`（当前有值）⇒ 保持 `unmeasured` 不阻塞 | `test_ratchet_evidence_source_lost_is_blocked`（含反方向不阻塞断言）|
| Q4 | Important | 4 条真实数据测试把**当前缺陷状态**钉死（`total == 841`、CUtil 恰 7 条声明、要求 ≥1 个 `health==0` 的类且均值 ≤0.95、CEffectSystem 错位**必须存在**）⇒ Task 8（完备性修复 / 发射器排序）一动手就为**正确改动**报红 | ① `total >= vtable_baseline.json['total_slots']`（**不劣化关系**）；② CUtil 声明数改下界 `>= 7` + 按**成员**判定首地址（不按下标）；③ 均值上界放宽到 1.0、去掉"必须有 0 分类"，改为**条件断言**（有 0 分类 ⇒ 均值 <1；无 ⇒ 均值 >0.95）；④ CEffectSystem 改**关系式**（有错位 ⇒ health<1；无错位 ⇒ 必须全对） | 第 14 节四条（**保序**改造，全部绿） |
| Q5 | Minor | `--json`/`--baseline` 目标目录不存在 ⇒ 未捕获 `FileNotFoundError` traceback + exit 1（与"棘轮阻塞"**同信号**） | 两处写入各包 `try/except OSError` ⇒ stderr 报错 + **rc=2** | `TestCli.test_cli_write_failure_to_missing_dir_is_exit_2` |
| Q6 | Minor | 缺 `purecall` 声明级 kind 断言 | 补断言（`purecall`/`fn` ⇒ `'func'`；4 个合成 kind ⇒ ≠ `'func'`） | `test_decl_slot_order_kind_purecall_is_func` |
| Q7–Q9 | — | **deferred**（不做）：Ruling 5 静态守卫字面串匹配 · 无基线时 `report_to_dict` 缺 ratchet 键 · TDD 红态不可复现 | 见 §4 顾虑 4 | — |

## 2. Q1 的语义论证（为什么是"规模"而不是"比值"）

只比比值时，**缩小分母被奖励**：`slot_health = 命中/总数`，删掉"未被命中"的那部分
（未声明槽 / 无地址声明）比值就上升，而**验证面同时缩小**。旧实现据此 `improved` 并回写基线 ——
基线一旦变成"缩水后的 1.0"，把缺失证据**补回来**（Task 8 的完备性修复）反而让比值下降 ⇒
`BLOCKED` ⇒ **门禁拦住正确的修复**（CLAUDE.md 的"假失败"模式）。

⇒ `slots`（二进制槽数 = 证据规模）与 `count_denom`（槽数项验证面 = 声明数+无地址声明数+
未覆盖槽数）必须作为**单调不降**分量：与已有的"整类消失 = `missing` ⇒ 阻塞"完全同一语义
（**验证面不得缩小**）。

**关键不变量（真实数据 e2e 实测，`RenderTarget2` 141→140 槽 / `AStarPathFinder` 完备性修复）**：

1. 真实数据写基线 ⇒ rc=0；
2. 缩水后写基线 ⇒ **rc=1 且基线文件逐字未变**（缩水基线**永远写不进去** ⇒ 假失败的前提被消除）；
3. 缩水被拒后，真实数据重跑 ⇒ rc=0 `state=pass`（基线仍是正当修复的出发点）；
4. 完备性修复（按**槽序**补齐缺失声明，`slot_health 0.6667→1.0`，`slots 3→3` 不变）
   ⇒ `state=improved` + **回写基线**（**不被 BLOCKED**）。

## 3. 已知取舍（该棘轮的固有代价，写进了 docstring 与 `--write-baseline` help）

**有意的验证面缩小**（删掉一个**确认是错的**多余声明 ⇒ `count_denom` 下降）会被阻塞：
`--write-baseline` 只在 `decision.passed` 时落盘 ⇒ 无法自助重建。这是棘轮制"不接受静默缩水"
的直接代价；出路是显式重建基线（`--baseline` 指向新路径，或先移除旧基线文件再写）。
本仓 ratchet 只在**显式给出 `--baseline`** 时才生效（默认无基线 ⇒ 恒放行），故不构成死锁。

## 4. 顾虑（交接给复核 / Task 8）

1. **`count_denom` 单调是双刃**：删"多余声明"（`count_ok False→True`、count_health 上升）会被
   判 `down` ⇒ 阻塞。按简报要求纳入（`slots`/`count_denom`），但这是唯一一处可能对**正确改动**
   报红的路径。若 Task 8 遇到，请按 §3 显式重建基线，或由上层裁定把 `count_denom` 降级为
   非阻塞的观测项（改一行：`_SURFACE_METRICS = (METRIC_SLOTS,)`）。
2. **`improved` 语义收紧**：`improved = improved and not blocked`。旧行为是"有分量上升即为 True
   （即使被阻塞）"。想知道哪些分量上升请看 `components` 里 `status=='up'` 的条目；本仓无其他消费者。
3. **`slots` 单向偏严**：若将来注解里确认某槽不是 vtable 槽而删除，同样会阻塞（同上出路）。
4. **deferred 项未消除的残余风险**：
   * Q7（Ruling 5 静态守卫用**字面串**匹配 `"['methods']"`）⇒ 换个写法（如 `d.get("methods")`）
     即可绕过；本轮未动（避免与并发实现者冲突 + 不在 4 Important 内）。
   * Q8：无基线时 `report_to_dict` **没有** `ratchet` 键 ⇒ 消费方需自判"无基线"（而非读
     `state=='pass'`）。
   * Q9：TDD 红态（5 条新测试红）本轮已实测记录（`82 passed / 5 failed`），但**不可复现**为
     仓库内的红态测试（测试与实现同提交）。
5. **基线格式兼容**：`slots`/`count_denom` **旧基线里本来就有**（`build_baseline` 一直在写），
   故把它们升级为比较分量**不需要重建基线**；若某基线缺这两个键 ⇒ 走 `unmeasured`（不阻塞），
   不会假红。

## 5. R=1 证据链自检

* 只改 2 个文件（`git status --short` 逐字核实）；`git add` 只加这 2 个文件。
* 未跑管线：`loop|apply|export|codegen` **一次未运行**；未写 `data/status/**`（e2e 的基线/JSON
  全部落在 `/tmp/t5_*`）。
* 对 `data/annotations/**` 仍**只读**（`main()` 的注解目录硬拒未改）。
* 测试（收尾前同跑）：`test_vtable_decl_check.py` **87/0** · `test_vtable_slot_order.py` **35/0** ·
  `test_vtable_slot_classifier.py` **38/0** · `test_vtable_sig_infer.py` **68/0**。
* 无子代理（遵守"无子代理契约"）。
---

# R=2 修复轮：R=1 引入的**过严**路径（1 项，一行降级）

- **状态**：**DONE**
- **范围**（严格）：只改 `tools/vtable_decl_check.py` + `tests/test_vtable_decl_check.py`；
  **未**运行 `pipeline/cli.py loop|apply|export|codegen`；只读真实数据（`pal3/src` +
  `data/annotations/structs`），输出全部落 `/tmp`。
- **一行测试摘要**：**88 passed / 0 failed**（原 87 + 新 1）· 前序无回退 **35 / 38 / 68**
  （另跑 `test_layout_assert_gen` 73/0 · `test_vtable_verify` 52/0/3skip 均绿）。

## 1. Q7：`count_denom` 单调**过严** ⇒ 拦住正确清理

**病**：R=1 把 `_SURFACE_METRICS = (METRIC_SLOTS, METRIC_COUNT_DENOM)`（"验证面不得缩小"）。
但 `count_denom`（`声明数 + 无地址声明数 + 未覆盖槽数`）是**声明数**，它合法地随
**声明清理**变化 ⇒ 把"删任何声明"一律判 `down`，包括删掉**冗余/错误**声明。

**真实数据实测反例**（`CGameData.h` 的 `virtual ~CGameData() {}`，无地址注释、槽表里没有它）：

```
CGameData baseline:        slots=7 slot_health=1.0 count_health=0.875 count_denom=8 count_ok=False decl_addr=7 decl_addrless=1
CGameData after cleanup:   slots=7 slot_health=1.0 count_health=1.0   count_denom=7 count_ok=True  decl_addr=7 decl_addrless=0
R=1 (simulated old)  state=blocked  passed=False improved=False blocked=True  updated=None
     [('slot_health',1.0,1.0,'same'), ('count_health',0.875,1.0,'up'), ('slots',7,7,'same'), ('count_denom',8,7,'down')]
R=2 (shipped)        state=improved passed=True  improved=True  blocked=False updated=YES
     [('slot_health',1.0,1.0,'same'), ('count_health',0.875,1.0,'up'), ('slots',7,7,'same')]
```

工具**自己**判 `count_ok False→True`、`count_health 0.875→1.0`（**改善**），`slots`/`slot_health`
不变，却被 `count_denom 8→7 down` 判 `blocked`/`updated=None`；R=1 之前的实现对该改动是
`pass` 并回写基线 ⇒ **新增过严路径**（门禁拦住正确改动，与 CLAUDE.md 的"假失败"同型）。

**修法（控制器裁定，一行）**：`_SURFACE_METRICS = (METRIC_SLOTS,)`。
理由：`slots`（注解 vtables 槽数）才是真正的**验证面**；`count_denom`（声明数）合法地随
声明清理变化。`count_denom` 仍在 `build_baseline` JSON 里（可观测），只是**不参与棘轮判定**。

## 2. ⚠️ 关键验证：Q1 两洞**仍被封死**（由 `slots` 单分量）

| # | 场景 | R=2 结果 | 证据 |
|---|---|---|---|
| ① | 删**未声明**槽（2 槽 → 1 槽，声明不动）⇒ `slot_health 0.5→1.0` | **仍 blocked**（`improved=False`，`updated=None`） | `test_ratchet_undeclared_slot_removal_is_not_improved`：`slots 2→1 down` ⇒ 阻塞；断言该分量存在 |
| ② | 删声明**及其**槽（3 槽 3 声明 → 1 槽 1 声明）⇒ 三个 health 全 `same` | **仍 blocked** | `test_ratchet_declaration_and_slot_removal_does_not_pass`：`slots_total 3→1` ⇒ `slots down` 单分量即阻塞 |
| ③ | 删**冗余**声明（`count_denom 8→7`，`slots` 不变，`count_ok` 改善） | **现在 pass/improved + 回写基线**（正确清理不再被拦） | `test_ratchet_redundant_addrless_decl_removal_is_not_blocked` |

②的测试已同步改**强**：断言 `count_denom` **不再出现在 `d.components` 里** —— 否则"该洞被封死"
的理由会悄悄退回到那条过严路径上（降级后必须证明 `slots` 单分量足够，而不是靠 `count_denom`）。
③另加**反向守卫**：从清理后的基线出发把冗余声明加回来（`count_denom 7→8`）**不得**读成改善 ——
它真实地压低 `count_health`（比值分量下降）⇒ 仍 blocked，只是理由从"验证面缩小"换成"比值下降"
（降级不给"加冗余声明"开口子）。

## 3. TDD 记录（红 → 绿）

* **红**（改 `_SURFACE_METRICS` 之前，两文件都已改）：`86 passed, 2 failed` ——
  * `test_ratchet_redundant_addrless_decl_removal_is_not_blocked`：`AssertionError: (..., ('count_denom', 2, 1, 'down'))`
    （`count_health 0.5→1.0 up` 被 `count_denom 2→1 down` 压成 blocked）
  * `test_ratchet_declaration_and_slot_removal_does_not_pass`：断言 `count_denom` 不入 components 失败
    （`..., ('slots',3,1,'down'), ('count_denom',3,1,'down')`）
* **绿**（改一行后）：`88 passed, 0 failed, 0 skipped`。

## 4. 证据链自检

* 只改 2 个文件（`git status --short` 逐字核实）；`git add` 只加这 2 个文件。
* 未跑管线：`loop|apply|export|codegen` **一次未运行**；未写 `data/status/**`（真实数据运行
  的 `--json` 落在 `/tmp/vdc_r2.json`，`--baseline` 未传 ⇒ 无对比、无写回）。
* 对 `data/annotations/**` 仍**只读**。
* 文档同步（同文件内，不留在说谎状态）：模块头 docstring 的"第 4 类"、`ratchet_decide` docstring
  的分量清单与"有意缩小"段落、`_SURFACE_METRICS` 定义处注释，全部改为 `slots` 单分量并记录
  R=2 降级理由与实测数字。
* 外部消费者核查：全仓（排除本 2 文件）对 `_SURFACE_METRICS` / `_RATCHET_METRICS` / `count_denom`
  的引用**只在下述文档里**，**无代码消费者** ⇒ 降级不破坏调用方。
* 无子代理（遵守"无子代理契约"）。

## 5. 顾虑（交接给复核 / Task 8）

1. **失去"声明数不得缩小"这一层保护**（控制器已明示的取舍）：若有人**批量删掉正确的**声明
   （例如误删一整个类的声明而槽表另有来源），只要 `slots` 不变就不再被拦。当前 `slots` 直接
   来自二进制视图槽数（`BinaryView.slot_addrs`）⇒ 覆盖面仍在；但"注解里声明数塌缩"本身
   不再单调受保护。缓解：`count_health`（命中声明数 / 声明数+无地址+未覆盖槽数）**仍是**比值
   分量，删掉**被覆盖**的声明会让它下降 ⇒ 仍阻塞（③的反向守卫即钉死这一点）。
2. **真实注解未改动**：`CGameData` 的冗余注入虚析构**仍在**（本次只改工具，不动注解）⇒
   该类的 `count_ok` 仍是 `False`。Task 8 做该清理时按 R=2 应判 `improved` + 回写基线。
3. **基线兼容**：`count_denom` 在旧基线里本来就有，降级只是**不再读**它 ⇒ 无需重建基线；
   `slots` 的 `unmeasured`（旧基线缺该键）行为不变。
