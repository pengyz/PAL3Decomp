# Task 6 报告：编译产物对比（vtable 数据最终裁判）

**状态**：DONE_WITH_CONCERNS
**提交**：`0c6fde7eb`（只含 `tools/vtable_verify.py` + `tests/test_vtable_verify.py`，+2496 行）
**测试**：`python3 tests/test_vtable_verify.py` → **39 passed / 0 failed / 2 skipped**
（`VTV_LIVE=1` 真机编译轮 → **41 passed / 0 failed / 0 skipped**）

前序回归（同一工作区、同一次跑）：`test_vtable_slot_order` 35 ✓ ·
`test_vtable_slot_classifier` 38 ✓ · `test_vtable_sig_infer` **68** ✓ ·
`test_layout_assert_gen` 46 ✓ · `tools/vtable_verify.py --selfcheck` PASS。
（简报写的 sig_infer 66 是 Task 3 R=2 修复轮之前的数字；当前工作区该文件由并行实现者在改，
本轮实测 68，**不回退**。）

---

## 1. 交付 API（供 Task 8 / Task 5 消费）

**归约（两侧同构）**

| 函数 | 作用 |
|---|---|
| `name_key(name)` | mangled/文本符号名 → 可比名字键（`?ff@D3@@W7AEHXZ`→`D3::ff`；`??_ED@@$4…`→`D::~D`；`??_7D3@@6BA3@@@`→`D3::__vftable[A3]`；`_purecall`→`__purecall`） |
| `obj_vtables(path)` → `{sym: ObjVTable}` | .obj 侧表（槽 = **符号重定位名**，`value`=address point，`col_symbol`=RTTI COL） |
| `obj_vbtables(path)` | `??_8<Cls>@@7B@` 的字面量 DWORD（无 reloc） |
| `decode_adjustor_chain(read, addr)` | thunk 体解码（两侧共用；`read` 可为函数或镜像） |
| `resolve_obj_thunk(art, name)` | obj 内 thunk：**尾部 jmp 目标由 reloc 解**，静态量由指令解 |
| `normalize_obj_slots(...)` / `normalize_bin_slots(...)` → `list[NormSlot]` | 归一化槽（`key/kind/offset/dynamic/va`，`normalized` 给出二元组或**动态三元组**） |
| `PEImage` / `BytesImage` / `bin_table_from_image` / `bin_vbtable` | 二进制侧读表（VA→文件偏移、节判定、表长界定、vbtable） |

**对比与报告**

* `compare_tables(obj_slots, bin_slots, obj_col=…, bin_col=…, obj_vbtable=…, bin_vbtable=…)` → `CompareResult`
* `compare_vbtable(obj_vals, bin_vals)` · `render_report(result)` · `result.to_dict()`
* 偏差 kind：`slot_count` / `address_point_rtti` / `slot_key` / `slot_kind` / `this_adjust` /
  `vbtable_count` / `vbtable_value`；每条都带 **slot 下标 + kind**（简报要求）。

**强制发射**

* `ProbeSpec(cls, header, abstract, has_virtual_dtor, ctor_declared, pure_virtuals, strategies)`
* `build_probe_source(spec[, strategy])` · `compile_probe(...)` · `force_emit(spec, workdir, compiler=…)`
  → `EmissionResult`；全失败 → `EmissionError(probe_source=…, attempts=[…])`
* 策略：`object`（普通类构造全局对象）/ `derived`（抽象类具体派生 + 构造）/
  `dummy_ctor`（无虚析构抽象类：`Cls::Cls() { }` + 派生 shim 的 ctor **显式调用**它）
* **验收判据**：编译后必须能在 .obj 里看到 `??_7<Cls>@@`；否则换下一策略，绝不静默比 0 槽。

**CLI**：`--obj/--cls/--list/--json/--bin-base/--bin-vbtable/--probe-src/--selfcheck`
（退出码 0=一致 / 1=有偏差 / 2=用法或 IO 错）。

## 2. 真机证据（每条都可复现）

### 2.1 归约与 thunk 归一（本任务真机复现）

> ⚠️ **R=3 更正（全分支最终评审 Important I-2「报告 §2.1 输出删减」）**：本节原先只贴了每台
> `--list` 输出的**最后 1 张表**（`--list` 实为 **4 张**、`--cls D --list` 实为 **3 张**）⇒
> 读者会把"1 张"当成全量，且"其余表是否也解析对"无从核对。现补全**完整输出**（2026-09-25 R=3
> 实跑复现，命令与 `--obj` 同上；`/tmp/vt3.obj`、`/tmp/c2.obj` 为 Task 6 真机构建产物，可用下行
> `wine_cl.sh` 命令重生成）。

```
$ tools/wine_cl.sh /c /nologo /Od /GR /I… /Fo/tmp/vt3.obj data/status/_vtable_abi_probe_20260925/vt3.cpp
$ python3 tools/vtable_verify.py --obj /tmp/vt3.obj --list          # ← 4 张表（完整）
/tmp/vt3.obj：4 张表
  ??_7A3@@6B@（2 槽，COL=??_R4A3@@6B@，address point=4）
     [ 0] A3::ff                 fn                 ['A3::ff', 'fn']
     [ 1] A3::onlyA              fn                 ['A3::onlyA', 'fn']
  ??_7B3@@6B@（2 槽，COL=??_R4B3@@6B@，address point=4）
     [ 0] B3::ff                 fn                 ['B3::ff', 'fn']
     [ 1] B3::onlyB              fn                 ['B3::onlyB', 'fn']
  ??_7D3@@6BA3@@@（2 槽，COL=??_R4D3@@6BA3@@@，address point=4）
     [ 0] D3::ff                 fn                 ['D3::ff', 'fn']
     [ 1] A3::onlyA              fn                 ['A3::onlyA', 'fn']
  ??_7D3@@6BB3@@@（2 槽，COL=??_R4D3@@6BB3@@@，address point=4）
     [ 0] D3::ff                 adjustor_static    ['D3::ff', 'adjustor_static', 8]   ← 83 e9 08; e9 <rel>
     [ 1] B3::onlyB              fn                 ['B3::onlyB', 'fn']
$ python3 tools/vtable_verify.py --obj /tmp/c2.obj --cls D --list   # ← 3 张表（完整）；attack B-1 复合槽
/tmp/c2.obj：3 张表
  ??_7D@@6B@（2 槽，COL=??_R4D@@6B@，address point=4）
     [ 0] D::~D                  deleting_dtor      ['D::~D', 'deleting_dtor']
     [ 1] D::b                   fn                 ['D::b', 'fn']
     vbtable = [-4, 24]
  ??_7D@@6BA@@@（2 槽，COL=??_R4D@@6BA@@@，address point=4）
     [ 0] A::o                   fn                 ['A::o', 'fn']
     [ 1] D::o                   fn                 ['D::o', 'fn']
     vbtable = [-4, 24]
  ??_7D@@6BV@@@（2 槽，COL=??_R4D@@6BV@@@，address point=4）
     [ 0] D::~D                  composite          ['D::~D', 'composite', 'dynamic', 16]  ← 2b 49 fc; 83 e9 10; e9
     [ 1] D::o                   adjustor_vbase     ['D::o', 'adjustor_vbase', 'dynamic', 0]
     vbtable = [-4, 24]                                     ← ??_8D@@7B@（字面量，非 reloc）
```

* 补全后可核对的额外事实：`--cls D` 的 3 张表**各自**都带 `vbtable = [-4, 24]`（同一虚基布局的
  三个视图）；`??_7D@@6B@` 槽 0 走 `deleting_dtor`（而非 composite）⇒ 与 `??_7D@@6BV@@@` 的
  `composite` 形态**互为对照**，本节"归约 + thunk 归一"结论对全部 4/3 张表成立。

* COL 与 address point：真机 `??_7C2@@6B@` 符号 `value = 4` ⇒ COL 在 `value-4`，
  槽从 address point 数起（`test_rtti_col_prefix_detected_and_not_counted_as_slot`）。
* reloc 的**原始 COFF 索引**（含 aux 占位）：夹具把带 aux 的符号排在 reloc 目标之前
  （`test_aux_symbol_entries_do_not_shift_reloc_targets`）；实现**复用** `coff_vtable.parse_obj`。

### 2.2 二进制侧表长界定与既有工具**逐字同规则**

```
189 张真机表（ctor 实写起始）：槽序列 / confidence / 类族 / 断裂点 —— 0 分歧
```

固化为 `test_bin_table_matches_vtable_compare_on_real_binary`（PAL3.exe 缺失时 SKIP）。
⚠️ 踩坑留痕：`vtable_compare.bin_table` 依赖模块全局 `vtable_scanner.SECTIONS`，
不先 `SECTIONS = load_sections()` 会静默返回 **0 槽**（本任务第一次交叉核对踩到）。
`bin_table_from_image` 用镜像自身的节表，不受该全局状态影响。

### 2.3 真机 adjustor 槽归一（二进制侧）

```
PAL3.exe 0x56AB28 槽 2 = 0x42C8D0（83 e9 08; e9 88 6f ff ff ⇒ jmp 0x423860）
  ⇒ (gbLightObj::GetCGEntry(char), adjustor_static, 8)
0x423860 即该方法本体（objdump 确认）；扫描显示全库 38 个 adjustor 形态槽
```

### 2.4 惰性 COMDAT / 强制发射（本任务实测，决定探针策略）

| 形态 | /Od | /O2 /Ob2 /Oi /Ot /Oy |
|---|---|---|
| 普通类，定义虚函数但**不构造对象** | **0 张表** | 0 张表 |
| 普通类，构造（全局）对象 | 有表 | 有表 |
| 普通类，ctor 定义 out-of-line（未使用） | 有表 | 有表 |
| 抽象类（**未声明** ctor、无虚析构）+ 具体派生 + 构造 | 有表 | **缺基类表**（死存储消除吃掉基类 vptr 写） |
| 抽象类（声明 ctor）+ dummy `Cls::Cls(){ }` | 有表 | 有表 |

⇒ `force_emit` 默认 `/Od`；`derived` 在 /O2 的失败由**发射检查**捕获并报错
（`test_force_emit_live_o2_dead_store_caught`），不会退化成"0 槽对比通过"。

### 2.5 真机 RTTI 实测（**跨任务发现，见顾虑 1**）

```
original/PAL3.exe 全库 `.?AV` 串 = 6 条，全部是 CRT/STL：
  .?AV_Exception@@  .?AVexception@@  .?AVlogic_error@std@@
  .?AVlength_error@std@@  .?AVout_of_range@std@@  .?AVtype_info@@
189 张表中 base-4 落在 .rdata 的仅 5 张（目标无名；且该处无 .?AV 串 ⇒ 不是 COL）
```

⇒ **游戏类 vtable 没有 RTTI COL**。而本仓管线编译**带 `/GR`**
（`pipeline/compare.py:69/81`、`pipeline/cli.py:690`）⇒ 一旦 obj 侧出现 `??_R4…`，
`address_point_rtti` 偏差就是真发现（目标表少 4 字节、逐槽地址位移）。

## 3. 顾虑（需 Ruling）

1. **【跨任务 / 可能影响 C-V 路线】RTTI COL 与目标不符**：目标无游戏类 RTTI，
   而管线（`/GR`）会发射 COL。若原版确为 `/GR-`，则任何虚类的 `.rdata` 表都会多 4 字节，
   byte-match 在 vtable 维度上**结构性不可能**达成——这不是本工具能修的，需在
   annotation/编译选项层裁定（或证明目标某处确有 RTTI）。本工具只负责把该偏差**逐槽报出来**。
2. **二进制表长界定是启发式**（沿 `vtable_compare` 三信号）：结果带 `confidence` 与
   `broken_at`，`low` 必须人工核；本工具不"裁定"表边界，只报告。
3. **MI 继承槽的名字归属**：obj 侧保留**基类** mangled 归属（`A3::onlyA`），二进制侧名字
   来自注解/IDA 显示名（可能写派生类 `D3::onlyA`）⇒ 会报 `slot_key`。我**故意不自动判等**
   （把 `A3::ff` 当 `D3::ff` 会放过"表里装了错误基类函数"的真错），只在 detail 里留痕提示。
4. **vbtable 维度需要二进制 VA**：`--bin-vbtable` 已实现（`bin_vbtable` 有单测），
   但真实类的"二进制 vbtable VA"目前无数据源（Task 8 的"IDA 二进制→证据 JSON"生产者可补）；
   缺一侧时**留痕不静默**（`test_missing_one_side_vbtable_leaves_trace`）。
5. **`force_emit` 的 ctor 可定义性是外部约束**：`dummy_ctor` 要求类**声明过** ctor；
   未声明且 /O2 时抽象类只剩 `derived`（可能被死存储消除）⇒ 报 `EmissionError`。
   真实消费方（Task 8）需要从头文件/注解提供 `ctor_declared` 与纯虚清单。
6. **name_key 覆盖边界**：嵌套类（`?f@Inner@Outer@@`→`Outer::Inner::f`）已处理；模板、
   运算符重载的 mangled 特殊形态未做专项金样本（不影响本任务实测类）。

## 4. 有意不做（边界）

* 槽序**逆映射**（attack A-1/A-3 证伪）→ Task 5/7；本模块只做**正向**逐槽对比。
* 签名推断（Task 3）与声明校验（Task 5）不在本模块；`classify_slot` 只消费原始指令/符号。
* 不跑 `pipeline/cli.py loop|apply|export|codegen`（并发约束），不碰
  `vtable_sig_infer.py` / `vtable_slot_order.py` / `vtable_slot_classifier.py` /
  `stage3_cleanup.py`。

## 5. TDD 留痕

* 先写 `tests/test_vtable_verify.py`（含最小合法 COFF 写出器 + 内存镜像夹具，全部 hermetic）
  → 红相：`ModuleNotFoundError: No module named 'vtable_verify'` → 33 红 → 实现 → 全绿。
* 真机 LIVE 测试（`VTV_LIVE=1`）单独一档，默认 SKIP（不把 wine 的慢/脆引入默认套件）。
* 全部默认夹具预期值均有真机复现命令写在各测试 docstring 里。

---

# 修复轮 R=1（必修 C1：符号名 → VA 归约序列未在交付路径实现）

**状态**：DONE（C1 闭环；残项与边界见 R1.6）
**改动**：`tools/vtable_verify.py` + `tests/test_vtable_verify.py` —— **只这两个文件**
**测试**：`python3 tests/test_vtable_verify.py` → **52 passed / 0 failed / 3 skipped**
（`VTV_LIVE=1 python3 tests/test_vtable_verify.py` → **55 passed / 0 failed / 0 skipped**）
本轮 **+14 测试**；原 39 条**零回退**（唯一改动是 `test_va_reduction_identity_prefers_va`
的 bin 侧调用——C1 要求 bin 侧**不再**名字反查，见 R1.1 第 2 条）。

## R1.1 三处病灶 → 修法（缺一不可）

| # | 病灶（修复前） | 修法 | 落点 |
|---|---|---|---|
| 1 | `main()` 对比模式**不传** `va_of`（`normalize_obj_slots(tbl, art)`）⇒ obj 侧 `va` 恒 None | `namemap = name_to_va_index(idx, image)` → `normalize_obj_slots(tbl, art, va_of=namemap)` | `main()` |
| 2 | `normalize_bin_slots` 用 `resolve(key)` **名字反查**，丢掉已经算出来的真实目标 VA（同源缺陷） | `va` **直接取** `th.target_va`（thunk 槽）/ 槽自身 VA（普通槽）；**删除** `va_of` 参数 | `normalize_bin_slots` |
| 3 | `identity` 恒退化 `('key', 名字文本)` ⇒ `identity_mode` 恒 `'name'`；两侧键空间本就不同（decomp 带参数表 / mangled 不带）⇒ 表正确也误报 | 新增 `strip_param_list` + `NormSlot.name_id`；`compare_tables` 逐槽：**两侧都有 VA ⇒ 比 VA，否则比 `name_id`**（绝**不**混比两种判据） | `NormSlot` / `compare_tables` / `_inherited_alias_hint` |

新增 API：`strip_param_list(name)`、`name_to_va_index(index, image=None)`、`NormSlot.name_id`。
**契约变更**：`normalize_bin_slots(table, image, index=None)`（去掉 `va_of`——bin 侧的真实 VA 是
**字节证据**，不需要任何映射；保留一个不生效的参数比删掉更糟）。`__all__` 已同步。

### `name_to_va_index` 的三条规则（都有真机证据，不猜）

1. **参数表剥离**（`_PARAM_LIST_RE = r'\(.*\)\s*$'`）：真机 `va_index()` 3618 条里 **3185** 条带
   参数表；obj 侧 `name_key()` 只取类令牌链 + 函数名 ⇒ **永远不带**。
2. **thunk 名字重定向到 `jmp` 目标**（给了 `image` 时用 `decode_adjustor_chain` 的**字节**判）：
   真机 0x42C8D0 的 idx 名是 `gbLightObj::GetCGEntry(char)`——名字挂在 **thunk 自身**上，
   而它的 jmp 目标 0x423860 在 idx 里**没有名字**。不重定向就会把 obj 侧指到 thunk 地址
   ⇒ 表正确反而报 `slot_key`（真机实测 **8 处**，全是 adjustor thunk；重定向后 **0 处**）。
   真机共命中 **103** 条重定向（79 条是 `e9 <rel>; padding` 形态的跳转桩，24 条是
   `sub ecx,N; jmp`）——bin 侧 `image_thunk()` 对同一批给出**同一目标** ⇒ 两侧判据一致。
3. **歧义名剔除**：归一后同名多目标（重载，真机 `CCBStage::DoTask` 等 **53** 例）⇒ 不进映射
   ⇒ 该槽退回名字判据（**不猜**一个 VA）。

## R1.2 红相 → 绿相（同一夹具可比）

```console
$ python3 /tmp/r1_evidence.py     # 夹具=真机 0x56AB28 形态；模块=修复前(/tmp/oldvt 隔离副本)/修复后
修复前: obj va=[None, None, None] bin va=[None, None, None] -> ok=False identity_mode=name deviations=3
    slot_key   slot 0: obj=gbLightObj::GetAABBox | bin=gbLightObj::GetAABBox(gbAABBox *)
    slot_key   slot 1: obj=gbLightObj::GetGfxManager | bin=gbLightObj::GetGfxManager(void)
    slot_key   slot 2: obj=gbLightObj::GetCGEntry | bin=gbLightObj::GetCGEntry(char)
修复后: obj va=[4198400, 4198416, 4198432] bin va=[4198400, 4198416, 4198432] -> ok=True identity_mode=va deviations=0
```
（`/tmp/oldvt` = `git show HEAD:tools/vtable_verify.py` 的隔离副本 + 符号链接复刻仓根，
**不改动工作区**；4198400/4198416/4198432 = 0x401000 / 0x401010 / 0x401020。）

实现前的那一刻，新增的 12 条测试里 **9 条红**（另 3 条是 API 缺失的 ImportError），红灯原文：

```console
$ python3 tests/test_vtable_verify.py          # 实现前
  FAIL test_compare_decomp_param_names_vs_mangled_obj_is_ok: AssertionError: (Deviation(kind='slot_key', index=0, obj='gbLightObj::GetAABBox', bin='gbLightObj::GetAABBox(gbAABBox *)', ...), ... index=1 ... index=2 ...)
  FAIL test_cli_compare_path_resolves_va_identity: AssertionError: (1, '{ "ok": false, ... "identity_mode": "name", ... "deviations": [ slot 0/1/2 slot_key ... ] }')
  FAIL test_cli_compare_real_gblightobj_table_is_clean: AssertionError: vtable 对比：... vs 0x56AB28
  FAIL test_bin_slot_va_is_known_target_or_slot_va_never_name_lookup: AssertionError: [... va=None ...]
  FAIL test_compare_passes_by_param_stripped_name_when_va_unavailable: ...
  FAIL test_inherited_alias_hint_survives_param_list: AssertionError: slot 0 目标不同：obj=A3::onlyA bin=D3::onlyA(char)
  FAIL test_va_reduction_identity_prefers_va: AssertionError: [... va=None ...]
  FAIL test_name_to_va_index_...: ImportError: cannot import name 'name_to_va_index'
  FAIL test_strip_param_list_...: ImportError: cannot import name 'strip_param_list'
  FAIL test_real_binary_slot_identity_index_is_self_consistent: ImportError: ...
Results: 40 passed, 11 failed, 2 skipped
```
**CLI 对比路径此前零测试覆盖**（C1 全绿漏过的病因）已补：
`test_cli_compare_path_resolves_va_identity`（真 `PEImage` + 最小真 PE 夹具，只 patch
`EXE`/`load_va_index`/`load_bin_targets` 三个**数据源**）+ 反向控制
`test_cli_compare_path_reports_wrong_slot_target`（.obj 槽装错函数 ⇒ rc=1 + slot 1/slot_key）。

## R1.3 真机量化：误报 ≥552 → 146（真机 187 表 / 639 槽）

| 类别 | 槽数 | 修复前 | 修复后 |
|---|---|---|---|
| bin 键带参数表（`gbLightObj::GetGfxManager(void)`…） | 406 | 必报 `slot_key` | **VA 判据，0 冲突**（obj 侧名字→VA 可解析） |
| bin 键退化成 `0x<VA>`（idx 无名字） | 146 | 必报 `slot_key` | 仍报，但**报告注明原因**（见下） |
| 合计 | **552** | ≥552 误报 | **146**（= 552 − 406） |

真机全库自洽性（`test_real_binary_slot_identity_index_is_self_consistent`）：187 表 / 639 槽中
**469** 槽 obj 侧 VA 可归约，**0 处冲突**（修复前 8 处，全是 adjustor thunk）。

## R1.4 真机端到端（评审引作 C1 证据的 0x56AB28）

```console
$ python3 tools/vtable_verify.py --obj /tmp/gb_light_obj.obj --cls gbLightObj --bin-base 0x56AB28
vtable 对比：/tmp/gb_light_obj.obj:??_7gbLightObj@@6B@  vs  0x56AB28
  槽数：obj 3 / bin 3（identity=va）
  RTTI COL：obj 无 / bin 无
  address point 偏移：obj 0 / bin 0
  ✅ 逐槽一致
EXIT=0
```
（.obj = 与真表同形的夹具；**idx / ctor 表起始 / thunk 字节全是真机**。修复前该表 3 槽全报。）

**修复不得变成放行**——真机确有偏差的表仍报：

```console
$ python3 tools/vtable_verify.py --obj build/.../AStarPathFinder.cpp.obj --cls AStarPathFinder --bin-base 0x56a600
  槽数：obj 2 / bin 3（identity=va）
  ❌ 4 处偏差：address_point_rtti / slot 2 slot_count /
     slot 0 slot_key（VA判据）obj='AStarPathFinder::IsInBounds' bin='AStarPathFinder::~AStarPathFinder(char)' /
     slot 1 slot_key（VA判据）obj='AStarPathFinder::GetHeuristicIdx' bin='AStarPathFinder::IsInBounds(int,int)'
EXIT=1
```
真机 10 对（.obj × 匹配真机表）修复前后**偏差逐一相同**（减少 0 对 / 增加 0 对 / 相同 10 对）——
即本轮**只**去掉假报，没有引入假通过（脚本 `/tmp/cmp_real.py`，用 `/tmp/oldvt` 隔离副本对比）。

## R1.5 测试与回归（命令 + 输出原文）

```console
$ python3 tests/test_vtable_verify.py
Results: 52 passed, 0 failed, 3 skipped          # 原 39 条全在；+13 默认测试（+1 LIVE）

$ VTV_LIVE=1 python3 tests/test_vtable_verify.py
  PASS test_force_emit_live_dummy_ctor_strategy  # R=1 顺带项 I2 新增
Results: 55 passed, 0 failed, 0 skipped

$ python3 tools/vtable_verify.py --selfcheck
selfcheck: PASS（??_7D3@@6BA3@@@ 槽 2 COL=??_R4D3@@6BA3@@@）

$ python3 tests/test_vtable_slot_order.py        → Results: 35 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_slot_classifier.py   → Results: 38 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_sig_infer.py         → Results: 68 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_decl_check.py        → Results: 87 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_call_transform.py    → Results: 35 passed, 0 failed, 0 skipped
$ python3 tests/test_layout_assert_gen.py        → Results: 73 passed, 0 failed, 0 skipped
```
新增测试清单（14 条，全部在 `tests/test_vtable_verify.py` §6）：
`test_strip_param_list_normalizes_decomp_names_to_obj_key_space` ·
`test_name_to_va_index_strips_params_and_redirects_thunk_names_to_target` ·
`test_bin_slot_va_is_known_target_or_slot_va_never_name_lookup` ·
`test_obj_slots_resolve_va_from_param_stripped_decomp_name_index` ·
`test_compare_decomp_param_names_vs_mangled_obj_is_ok` ·
`test_compare_passes_by_param_stripped_name_when_va_unavailable` ·
`test_compare_still_reports_wrong_target_with_decomp_style_names` ·
`test_inherited_alias_hint_survives_param_list` ·
`test_compare_notes_when_name_criterion_has_unnamed_side` ·
`test_cli_compare_path_resolves_va_identity` ·
`test_cli_compare_path_reports_wrong_slot_target` ·
`test_cli_compare_real_gblightobj_table_is_clean` ·
`test_real_binary_slot_identity_index_is_self_consistent` ·
`test_force_emit_live_dummy_ctor_strategy`（LIVE）。

## R1.6 顺带项与残项

* **M1（`normalized` 静态三元组 vs 简报"二元组"）**：语义等价，**保留三元组**，语义说明写进
  `NormSlot.normalized` docstring（`(目标函数, kind, this 调整量)`；"二元组"指
  `(目标函数, this 调整量)` 这一语义，`kind` 维是 Task 2 词表要求的归一分量）。
* **M2（`address_point_offset` 只打印不判定）**：**文档化**而非加判定——COL 存在性已由
  `address_point_rtti` 判据覆盖；加判定会与它重复报同一事实（且会让
  `test_address_point_rtti_deviation` 的"两侧提供 COL"用例变红）。已写进 `compare_tables` docstring。
* **I2（`dummy_ctor` 无 LIVE 覆盖）**：已补 `test_force_emit_live_dummy_ctor_strategy`
  （抽象类 + 无虚析构 + **声明了 ctor** ⇒ `default_strategies` 首选 dummy ctor；
  断言 `res.strategy == PROBE_STRATEGY_DUMMY_CTOR`，不是"某条策略过了"）。
* **残项（146 槽，不在 C1 修法射程内）**：bin 侧在 idx 里**没有名字**（79 槽是 import stub
  `ff 25 <IAT>`、67 槽是未命名函数本体）⇒ `name_id` 是 `0x<VA>` 占位，obj 侧名字在 idx 里
  无覆盖 ⇒ **VA 与名字两条判据都不可用**。此时**保守报 `slot_key` 不静默放过**，并在
  `CompareResult.notes` 写明原因（`test_compare_notes_when_name_criterion_has_unnamed_side`）。
  要真正消掉这 146 槽得先补**名字源**（补 idx/注解覆盖，或解析 PE import 表把 `ff 25 <IAT>`
  变成导入符号名）——属**新增特性**，未在本轮做（真机 10 对可比 .obj 里没有这类表）。
* **已知边界（新增判据）**：VA 判据对 **COMDAT 折叠别名**（同体不同 VA）会假报；
  真机 187 表实测 **0 冲突**，管线未观测到该形态，留档待验。

---

# 修复轮 R=2（歧义名剔除引入的**静默假通过**：真重载装错被判相同）

**状态**：DONE_WITH_CONCERNS（主假通过面已挡；同签名组仍是包含判据，见 R2.6）
**改动**：`tools/vtable_verify.py` + `tests/test_vtable_verify.py` —— **只这两个文件**
**测试**：`python3 tests/test_vtable_verify.py` → **61 passed / 0 failed / 3 skipped**
（`VTV_LIVE=1 python3 tests/test_vtable_verify.py` → **64 passed / 0 failed / 0 skipped**）
本轮 **+9 测试**；原 52 条**零回退**；前序门禁 35/38/68/88/35/73 **零回退**（见 R2.5）。

## R2.1 病灶：C1 的「歧义名剔除」把判据退化成抹掉参数的名字文本

真机坐标系（**本轮实测双证**：`load_va_index()` 与 IDB 导出 `pipeline/ida/_logs/func_bounds.json`
的真 mangled 名逐条对上，后者**只作独立 ground truth**，不是工具输入）：

| 表 / 槽 | 槽内目标 | idx 名（decomp/注解） | IDB 真 mangled 名（func_bounds） |
|---|---|---|---|
| `0x56F674` 槽 0 | `0x4C1640` | `RenderTarget2::DestroyEffBase(char)` | `?DestroyEffBase@RenderTarget2@@QAEPADD@Z` |
| （组内另一候选） | `0x4C1660` | `RenderTarget2::DestroyEffBase(void)` | `?DestroyEffBase@RenderTarget2@@QAEHXZ` |

* 真机 **189 张表 / 639 槽**里，`name_id` 在 idx 里对应 **≥2 个 VA** 的槽 = **24 个（3.8%）**，
  涉及 **12 个 name_id**（实测脚本 `/tmp/measure_impl.py`，输出见 R2.4）。
* R=1 的 `name_to_va_index` 只能表达单值 ⇒ 这些名字**整体剔除** ⇒ obj 侧 `va=None` ⇒
  `compare_tables` 走名字判据，而两侧键都被 `name_key` 抹成
  `RenderTarget2::DestroyEffBase` ⇒ **判相同**。
* 这 24 槽的 `name_id` **全部**等于参数表剥离后的 key（24/24，实测）⇒ **纯名字判据对它们
  的判别力为零**：无论 .obj 装哪个重载（甚至装错）都判相同。

## R2.2 修法（控制器裁定：候选集 + 包含判据）＋ 两处真机倒逼的加固

| # | 修法 | 落点 |
|---|---|---|
| 1 | 歧义名**保留候选集**：新增 `name_to_va_candidates(idx, image)` → `{名字键: {VA: idx 名}}`（同名多目标全留；单值投影 `name_to_va_index` **契约不变**，仍是"歧义名剔除"） | `_name_candidate_groups` / `name_to_va_candidates` |
| 2 | `.obj` 侧**用符号自身的参数编码把候选集收敛**到具体重载：idx 参数文本 → mangled 参数后缀（借管线 `vc6_mangler.encode_type`），要求**恰好一个**候选的后缀命中 | `_param_suffix_variants` / `_refine_candidates_by_symbol` |
| 3 | 收敛不了（idx 名同签名 / 编码不可确定）⇒ **包含判据** `bin.va ∈ 候选集`；两侧都只有候选集 ⇒ 交集非空 | `_slot_identity_decision` |
| 4 | **只有**两侧都没有任何 VA 信息时才退回纯名字判据（行为与 R=1 一致） | 同上 |
| 5 | `main()` 交付路径改用候选集映射（`va_candidates_of=name_to_va_candidates(idx, image)`） | `main()` |
| 6 | 偏差报告带 VA 坐标（`（VA obj=0x004C1660 bin=0x004C1640）`）+ 候选集/收敛留痕（`NormSlot.notes` / `va_candidates`） | `compare_tables` / `NormSlot` |

**收敛判据的三个前提**（任一不成立就**不收敛**，退回包含判据——宁可少一分特异性，不可多一分假报）：

1. 候选名**都**带参数表且编码可确定（数组/函数指针/引用/模板/可变参 ⇒ 直接判"不可确定"）；
2. 各候选编码**互不相同**（同签名重载本来就不该收敛）；
3. 恰好**一个**候选的编码是 `.obj` 符号的后缀。

**两处加固都是真机量化倒逼出来的（本轮实测发现 → 修 → 复测）**：

* `_swap_class_tag`：`vc6_mangler.encode_type` 的 `ptr > 0` 分支**先于** tag 分支（第 75 行 vs
  第 87 行）⇒ `struct X *` 仍编成 `PAVX@@`（tag 被丢）。真机代价：
  `CCBStage::DelTask(int,_BYTE *,int *)`（真名 `...HPAU_BYTE@@PAH@Z`）编码失败，另一个候选
  `(int)`（`H@Z`，恰好是长名的后缀）成了唯一命中 ⇒ **把正确重载误报成错装**
  （修前实测 **1/112** 个有真名候选命中此坑；修后 **0**）。回归测试
  `test_correct_struct_pointer_overload_is_not_false_reported`（红相已单独复核：把
  `_swap_class_tag` 打回 `None` ⇒ `?DelTask@...PAU_BYTE@@PAH@Z` 收敛成 `0x50A8E0` ⇒ 假报）。
* 本类引用的**两种**真机形态都要收：回指 `1@`（mangler 规则 F61，返回类型处）**与**全名
  （实测 `?Create@CEffgbParticle@@QAEPAXPAUCEffgbParticle@@D@Z` 的**参数**就是全名）⇒ 只收一种
  会把另一种判成"编码失败"。
* `uint → unsigned int` 别名归一：`vc6_mangler._TC` 没有 `uint`，不归一会兜底成 `int`（`H`）
  而真名是 `I`（真机 `_sdtor_*(uint)` 组 5 槽因此编码失败）。

## R2.3 红相 → 绿相（真机表 `0x56F674`，夹具=真机形态 .obj，坐标双证）

```console
$ python3 /tmp/red_green.py     # 真 PAL3.exe + 真 load_va_index + 真表 0x56F674；.obj 槽 0 装 (void)
## ① 修复前（R=1 交付路径：name_to_va_index + 名字判据）
obj 槽 0 符号 = ?DestroyEffBase@RenderTarget2@@UAEXXZ（真值应为 0x004C1660）
obj 槽 0 归一：va=None resolution='name'
compare_tables: ok=True identity_mode='mixed' deviations=0          # ← 静默假通过

## ② 修复后（R=2 交付路径：name_to_va_candidates + 收敛/包含判据）
obj 槽 0 归一：va=4986464 va_candidates=(4986432, 4986464) resolution='va'
obj 槽 0 注：('名字歧义（同一 name_id 对应 2 个候选 VA {0x004C1640, 0x004C1660}）：
              按 .obj 符号?DestroyEffBase@RenderTarget2@@UAEXXZ 的参数编码收敛到 0x004C1660',)
compare_tables: ok=False identity_mode='va' deviations=1
    slot 0   slot_key   ... slot 0 目标不同（VA判据）：obj=RenderTarget2::DestroyEffBase
             bin=RenderTarget2::DestroyEffBase(char)（VA obj=0x004C1660 bin=0x004C1640）
```

TDD 红灯原文（实现前那一刻，`python3 tests/test_vtable_verify.py`）：

```console
Results: 52 passed, 8 failed, 3 skipped
FAIL test_cli_overload_path_reports_wrong_variant_on_real_table:
  AssertionError: (0, 'vtable 对比：…/rt2.obj:??_7RenderTarget2@@6B@  vs  0x56F674
    槽数：obj 2 / bin 2（identity=mixed）
    ✅ 逐槽一致
    ⚠️ 表长界定置信度 low（在 CEffSParticle(0x4D33A0) 处断裂 ⇒ 需人工核）')      # ← rc=0 静默放行
FAIL test_ambiguous_slot_with_wrong_overload_reports_deviation: ImportError: name_to_va_candidates
FAIL test_name_to_va_candidates_keeps_ambiguous_overloads:       ImportError: name_to_va_candidates
FAIL test_ambiguous_slot_with_correct_overload_passes:           ImportError: name_to_va_candidates
FAIL test_real_ambiguous_name_candidates_cover_render_target_overloads: ImportError
FAIL test_ambiguous_slot_falls_back_to_candidate_containment:    TypeError: va_candidates
FAIL test_both_sides_candidates_require_nonempty_intersection:   TypeError: va_candidates
FAIL test_cli_overload_path_passes_correct_variant_on_real_table: AssertionError: identity=mixed
```

CLI 交付路径两个方向的原文（真 `PAL3.exe` + 真 idx + 真表 `0x56F674`）：

```console
$ python3 tests/test_vtable_verify.py     # 用例内 CLI 调用 --cls RenderTarget2 --bin-base 0x56F674
### 错装 (void) ⇒ exit=1
  ❌ 1 处偏差（定位到槽位 + kind）：
    slot 0   slot_key   obj='RenderTarget2::DestroyEffBase'  bin='RenderTarget2::DestroyEffBase(char)'
             slot 0 目标不同（VA判据）：…（VA obj=0x004C1660 bin=0x004C1640）
### 正确 (char) ⇒ exit=0
  ✅ 逐槽一致
```

## R2.4 真机量化（189 表 / 639 槽；脚本 `/tmp/measure_impl.py`、`/tmp/measure_dir3.py`）

```console
真机表 189 张 / 槽 639 个；名字歧义槽 24 个（3.8%）；涉及 12 个 name_id
歧义组 53 个；有真名的候选 112 个：收敛到子集 83（其中收敛到单值 82）、假报风险 0
表 0x56F674 槽: [('0x4c1640', 'RenderTarget2::DestroyEffBase(char)'),
                ('0x4c2170', 'RenderTarget2::AllocTargets(int)')]
func_bounds: {'0x4c1640': '?DestroyEffBase@RenderTarget2@@QAEPADD@Z',
              '0x4c1660': '?DestroyEffBase@RenderTarget2@@QAEHXZ'}
候选集: {'0x4c1640': 'RenderTarget2::DestroyEffBase(char)',
         '0x4c1660': 'RenderTarget2::DestroyEffBase(void)'}
单值投影含该名? False                      # R=1 契约未变
24 槽名字 id == 参数表剥离后的 key（⇒ 纯名字判据恒判相同）：24/24
24 槽错装方向（组内其他候选，有真名）25 例 ⇒ 修复后判死 15；仍静默放行 10；无可试（无真名）4
```

* **假报风险 0/112**（判据："以每个候选**自己的真名**当 `.obj` 符号，收敛结果必须含它"）——
  这条是**健全性**判据：不满足就是把正确重载误报成错装（R2.2 的两处加固正是为它做的）。
* 错装方向 **15/25 判死**（`RenderTarget2::DestroyEffBase` 属其中之一）；剩余 **10 例全是
  `scalar deleting destructor` 同签名组**（3 个 `UIWnd` + 3 个 `UIFrameWnd` 槽 × 组内其他候选），
  它们的 idx 名**逐字相同**（`Cls::\`scalar deleting destructor\'(uint)`）、真符号是 IDA 伪名
  `?_sdtor_14@…` ⇒ 参数编码**不可能**区分 ⇒ 走包含判据（见 R2.6 残项）。

## R2.5 测试与回归（命令 + 输出原文）

```console
$ python3 tests/test_vtable_verify.py
Results: 61 passed, 0 failed, 3 skipped          # 原 52 条全在；+9 默认测试

$ VTV_LIVE=1 python3 tests/test_vtable_verify.py
Results: 64 passed, 0 failed, 0 skipped

$ python3 tools/vtable_verify.py --selfcheck
selfcheck: PASS（??_7D3@@6BA3@@@ 槽 2 COL=??_R4D3@@6BA3@@@）

$ python3 tests/test_vtable_slot_order.py        → Results: 35 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_slot_classifier.py   → Results: 38 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_sig_infer.py         → Results: 68 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_decl_check.py        → Results: 88 passed, 0 failed, 0 skipped
$ python3 tests/test_vtable_call_transform.py    → Results: 35 passed, 0 failed, 0 skipped
$ python3 tests/test_layout_assert_gen.py        → Results: 73 passed, 0 failed, 0 skipped
```

⚠️ `test_vtable_decl_check.py` 本轮实测 **88**（R=1 报告写 87）：该套件**不 import
`vtable_verify`**（`grep -n vtable_verify tests/test_vtable_decl_check.py` 零命中）⇒ 与本轮改动
无关，差异来自 Task5 R=2（`f87ea44b7`）落地后的用例数；本轮未碰它。

新增测试清单（9 条，全部在 `tests/test_vtable_verify.py` §7）：
`test_name_to_va_candidates_keeps_ambiguous_overloads` ·
`test_ambiguous_slot_with_wrong_overload_reports_deviation` ·
`test_ambiguous_slot_with_correct_overload_passes` ·
`test_ambiguous_slot_falls_back_to_candidate_containment` ·
`test_both_sides_candidates_require_nonempty_intersection` ·
`test_cli_overload_path_reports_wrong_variant_on_real_table` ·
`test_cli_overload_path_passes_correct_variant_on_real_table` ·
`test_correct_struct_pointer_overload_is_not_false_reported` ·
`test_real_ambiguous_name_candidates_cover_render_target_overloads`。

**并发约束遵守**：未跑 `pipeline/cli.py loop|apply|export|codegen`；只改上述两个文件；
`func_bounds.json` 仅**只读**用作独立 ground truth（工具不读它）。

## R2.6 残项、边界与顾虑

1. **残项（10 例错装仍静默，真机）**：同签名歧义组（`_sdtor_*` / `_scalar_dtor`，idx 名逐字
   相同）在"只有名字与参数文本"的信息下**不可区分** ⇒ 包含判据对此**恒真**。要真正消掉，
   需要一份 **mangled 名 → VA 的精确索引**（IDB 的 `func_bounds.json` 里 `?_sdtor_14@UIWnd@@…`
   本身就是**每个 VA 各不相同**的真符号，可直接精确解析；本轮**未接**——那是新增数据源/特性，
   超出控制器裁定的修法射程）。当前形态**不劣于修复前**（修复前这 10 例同样静默，且 24 槽
   全部只有名字判据）。
2. **标注对齐风险**：收敛判据的输入是 **idx 参数文本**，它来自 decomp/注解，可能与真 mangling
   有偏差（本轮实测：`CEffgbParticle::Create` 的 idx 文本与真名在"本类指针是否回指"上不同）。
   已用"两种形态都收 + 全部候选必须可确定 + 编码互异 + 恰好一个命中"四道闸把**假报**压到
   实测 0/112；但 idx 文本偏差会让**收敛失败 ⇒ 退回包含判据**（特异性下降，不是假报）。
3. **`bin_table_from_image` 的表长上界有既存非确定性（本轮实测发现，未修）**：
   `nxt = [t for t in targets if t > base]; hard_end = nxt[0]`，而 `targets` 来自
   `load_bin_targets()` = **set** ⇒ `nxt[0]` 是**任意**一个更大的表起始，不是最近的那个。
   实测同一 `base=0x56F668` 在不同进程里读出 3 槽（正确：`end=0x56F674`）或 4+ 槽（越过下一张表）。
   本轮**不修**的理由：`tools/vtable_compare.py:153-154` 的参考实现（`bin_table`）是**同一写法**，
   而 `test_bin_table_matches_vtable_compare_on_real_binary` 逐字比对两者 ⇒ 只修一侧会让该一致性
   测试变红，而 `vtable_compare.py` 不在本轮许可改动范围（"只改这两个文件"）。**建议**：把它
   作为独立小任务，两侧同时改成 `min(nxt)`（本报告与本轮所有真机量化脚本都显式传
   `targets=sorted(...)` 规避）。
   ⚠️ 这也解释了控制器引用的坐标 `表 0x56f668 槽2`：**两处都真**——`0x56F674` 槽 0 直接装
   `0x4C1640`；`0x56F668` 槽 2 装的是 `0x4C2040`（一个 `jmp 0x4C1640` 的跳转桩，thunk 归一后
   目标同为 `0x4C1640`）。本轮两个坐标都实测过（见 R2.4 输出）。
4. **顺手修的一处报告误导（已加测试断言）**：`_inherited_alias_hint` 原先只比**方法名**，于是
   真重载（同名同类、参数不同）也会附上"仅归属类不同 ⇒ 可能是 MI 继承槽差异"，把操作员引向
   错误方向。已收紧为**归属类必须真的不同**才提示（R=1 的
   `test_inherited_alias_hint_survives_param_list` 仍绿），并在新测试里断言
   `'仅归属类不同' not in dev.detail`。
5. **`identity_mode` 语义**：候选集/收敛判据计入 `'va'`（它确实是 VA 空间的判据），并在
   `CompareResult.notes` 里单独留痕"N 槽以候选集判据判定"——避免把"候选集判据"读成"VA 精确相等"。
* **未跑**（并发约束）：`pipeline/cli.py loop|apply|export|codegen`；未触碰任何其他文件。