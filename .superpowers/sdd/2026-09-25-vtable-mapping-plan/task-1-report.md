# Task 1 报告：vtable 槽序验证规则（正向规则 + 金样本测试）

- **状态**: DONE
- **交付**: `tools/vtable_slot_order.py` + `tests/test_vtable_slot_order.py`（TDD：先测试红 → 实现绿）
- **测试**: `python3 tests/test_vtable_slot_order.py` ⇒ **35 passed, 0 failed, 0 skipped**
- **提交**: `4712eb9aa`（`tools/vtable_slot_order.py` + `tests/test_vtable_slot_order.py`）——本目录 `.superpowers/sdd/` 被本地 `.gitignore` 排除，报告不在提交内

---

## 1. 正向规则的精确表述（声明 → 槽序）

设本类 virtual 声明为 `d_0..d_{n-1}`（声明序），继承槽序（同一视图）为 `base`：

1. **继承槽原位保留，覆写原位替换**。按 `match_key` 匹配到 `base` 槽的声明替换该槽**槽位**
   （origin=override），不移动、不改变槽数。
2. **本地新增段尾插**。未匹配到任何继承槽的声明进入本地新增段，接在继承段之后；
   MI 下**只追加到主视图**（首基链），次视图不含新增槽。
3. **本地段内同名组逆序**。同名声明成组；**整组占据首现声明的组位**（连续区段）；组内按声明序
   **逆序**；组间按各组首现声明先后排列。
4. **合成槽（deleting_dtor/adjustor）落声明位，不参与同名分组**。每个合成声明构成**单槽组**，
   组位由其声明序在各组首现序中的秩决定；不与任何名字合并、不逆序、不浮动。

**打包细节（判别性实测，实现必须照做）**：

- **D1｜本地段按「全部」本地声明打包（含覆写），打包后再摘除覆写者**（摘除序 ≠ 重排序）。
  判别样本 DA（syn_probe2）：`decl[o(int)覆写, z, o(char*)] → 槽[o(int)@DA, o(char*)@DA, z]`；
  若只按新增声明打包 ⇒ `[o(int), z, o(char*)]`，slot1/2 互换 ⇒ **实测证伪**。
- **D2｜"落声明位" = 单槽组的组秩，不是字面声明下标**。P1（syn_probe）：
  `decl[o()(0), ~P1(1), o(int)(2)] → 槽[o(int), o(), ??_E]`，dtor 落**槽 2**；
  钉死字面下标 1 ⇒ `[o(int), ??_E, o()]` ⇒ **实测证伪**。adv3 的"落声明位（槽 0）"
  是首声明的特例。规则语义不变：合成槽不参与分组、组位纯由声明位置推出。

`match_key`：普通函数 = `(func, 名字, 参数, 方法 cv)`；合成槽 = `(kind, 参数, 方法 cv)`
（**名字不参与**——`~D()` 覆写 `~B()`）。顶层参数 cv 不区分签名（C++ 规则：`o(const int)` 覆写
`o(int)`），指针指向的 const 保留（`o(const char*)` ≠ `o(char*)`），方法 cv 参与（`o() const` ≠ `o()`）。

## 2. 设计决策

| # | 决策 | 依据 |
|---|---|---|
| 1 | **不用 mangling 识别合成槽**：合成性由**声明**给出（虚析构声明 ⇒ deleting_dtor 单槽组）；本模块 kind 是**声明级**标记 | 简报约束（真实二进制 531 槽仅 4 条 mangled）。槽**内容**分类（adjustor_static/adjustor_vbase/purecall/composite）属 Task 2 `vtable_slot_classifier` 词表，`SYNTHETIC_KINDS` 与之兼容 |
| 2 | 纯虚声明按普通虚函数参与规则（不作合成槽） | vt2 实测 Q `decl[p()=0,r()] → [__purecall, r]`，DQ 覆写原位替换 ⇒ 顺序维度与普通声明无异；__purecall 是槽内容 |
| 3 | MI = 按基链折叠视图；**一个声明可原位替换多个视图的多个槽**；新增段只进主视图 | abi README #1/#3（vt2/vt3 实测 `??_7D@@6BA@@@`/`6BB@@@`、`?ff@D3@@W7AEHXZ` adjustor） |
| 4 | **虚继承视图合成显式拒绝**（`NotImplementedError`），不猜 | attack README B-1..B-4（1 声明↔多视图多槽、声明落"异己视图"、动态 delta 不可归一）⇒ 归 Task 2/5/6；静默给错误槽序是 🔴 级风险 |
| 5 | 不实现任何反向映射（槽序→声明） | attack README A-1/A-3：逆映射不可还原且重发射错二进制（r1.cpp 实证） |
| 6 | API 形态：`layout_local_segment`（规则 3/4）／`compute_slot_order`（单视图全规则）／`compute_class_views`（MI 多视图） | Task 5 消费正向规则做槽数+槽序校验；Task 7 需 slot→method 映射——`SlotEntry(origin=继承/覆写/新增)` 直接可查 |

## 3. 金样本覆盖情况

**方法可信度**：三个 README 的全部 9 个探针源文件（vt6/vt7/adv2/adv3/adv4/vt6_repro/a1/a2/a3/a4）
由我用 README 的复现命令在真机 MSVC6 SP0 重新编译并用 `tools/coff_vtable.py` 重新提取，
**逐槽与 README 声称一致**（含 vt6_repro 对 #8 的复核）；另补 2 个新探针（syn_probe/syn_probe2）
澄清简报 4 的欠定维度。金样本 expected 值 = 这些**实测复核值**（测试内联硬编码，不依赖可删除的草稿目录）。

| 测试 | 金样本 | 证据 |
|---|---|---|
| test_t1/t2/t3/o_four_overloads | T1/T2/T3/O | abi README #8（+vt6/vt7.cpp 实测复核） |
| test_do_override_replaces_in_place… | DO : O | advprobe README vt6_repro 行 |
| test_q_pure_virtual_override… | Q/DQ | abi README #6 + vt2.cpp |
| test_dtor_override…first/mid_class | D7/D8 | **补充实测** syn_probe |
| test_adv2_new_overload_tail… | B2/D2 | advprobe README adv2 行 |
| test_adv4_tail_segment… | B3/D3 | advprobe README adv4 行 |
| test_adv3_deleting_dtor… | C3 | advprobe README adv3 行 |
| test_a1/a2/a3/a4 | B/D、Base/Der、B3/D3、B4/D4 | attack README A-1/A-2 |
| test_syn_dtor_mid_group… / before_last… / in_derived | P1/P2/P2b/D5 | **补充实测** syn_probe |
| test_syn_synthetics_never_group… | 纯逻辑锁定"不参与同名分组" | 规则 4 |
| test_d6_group_packs… / test_db_interleaved… / test_override_participates… / test_d9… | D6/DB/DA/D9 | **补充实测** syn_probe/syn_probe2（DA 为 D1 判别样本） |
| test_vt2_mi… / test_vt3… | D : A, B、D3 : A3, B3 | abi README #1/#2/#3 |
| test_virtual_base_rejected… | 拒绝契约 | attack README B-1..B-4 |
| test_match_key… / method_const… / top_level_const… / pointer_params… | 匹配键规则 | C++ 签名规则 + adv3（o() const 成组不覆写） |

README 三条主规则 + 简报 4 条规则均有 ≥1 金样本；判别维度（D1/D2）有专测。

## 4. 测试输出

```
$ python3 tests/test_vtable_slot_order.py
  PASS test_a1_new_overloads_form_own_segment_never_join_base_group
  PASS test_a2_der_overrides_in_place_plus_new_tail
  PASS test_a3_single_new_overload_tail_appends
  PASS test_a4_new_group_reversed_in_segment
  PASS test_adv2_new_overload_tail_appends_never_merges_into_base_group
  PASS test_adv3_deleting_dtor_first_decl_singleton_group
  PASS test_adv4_tail_segment_internal_group_reversal
  PASS test_d6_group_packs_across_interloper_in_derived_segment
  PASS test_d9_mixed_override_and_new_overloads_of_same_name
  PASS test_db_interleaved_group_packs_in_derived_segment
  PASS test_do_override_replaces_in_place_only_one_slot_changes
  PASS test_dtor_override_replaces_in_place_first_slot
  PASS test_dtor_override_replaces_in_place_mid_class
  PASS test_layout_local_segment_empty
  PASS test_match_key_owner_and_dtor_name_ignored
  PASS test_method_const_is_part_of_signature
  PASS test_o_four_overloads_fully_reversed
  PASS test_origin_labels_describe_current_class_only
  PASS test_override_participates_in_segment_packing_then_excised
  PASS test_pointer_params_not_const_flattened
  PASS test_q_pure_virtual_override_replaces_in_place
  PASS test_syn_dtor_declared_before_last_group_member
  PASS test_syn_dtor_in_derived_local_segment
  PASS test_syn_dtor_mid_group_const_overloads
  PASS test_syn_dtor_mid_group_is_singleton_group_not_pinned_index
  PASS test_syn_synthetics_never_group_with_each_other
  PASS test_t1_same_name_group_reversed
  PASS test_t2_distinct_names_keep_declaration_order
  PASS test_t3_group_packs_at_first_occurrence_and_interloper_moves_after
  PASS test_top_level_param_const_does_not_prevent_override
  PASS test_virtual_base_rejected_not_silently_wrong
  PASS test_vt2_mi_new_virtual_appends_only_to_primary_view
  PASS test_vt2_mi_secondary_base_override_replaces_in_place
  PASS test_vt2_root_class_views
  PASS test_vt3_one_decl_replaces_slots_in_both_views
Results: 35 passed, 0 failed, 0 skipped
```

TDD 红（实现前）：`ModuleNotFoundError: No module named 'vtable_slot_order'`（预期）。

⚠️ `python3 -m pytest` 在本环境**不可用**：环境自带 pytest 5.4.1.dev 的 assertion rewrite 在
py3.10 上崩溃（`TypeError: required field "lineno" missing from alias`），对既有测试
（`tests/test_audit_attribution.py`）同样崩溃 ⇒ 环境问题、非本任务引入；测试按仓库惯例
`python3 tests/<file>.py` 直跑（既有测试同惯例 20/20 通过）。

## 5. 复现

```sh
cd /home/peng/workspace/PAL3Decomp
INC=tools/compilers/msvc6.0/Include
# 三个金样本目录的 9 个源（README 复现命令）
for f in data/status/_vtable_abi_probe_20260925/vt6.cpp \
         data/status/_vtable_abi_probe_20260925/vt7.cpp \
         data/status/_vtable_advprobe_20260925/adv2.cpp \
         data/status/_vtable_advprobe_20260925/adv3.cpp \
         data/status/_vtable_advprobe_20260925/adv4.cpp \
         data/status/_vtable_advprobe_20260925/vt6_repro.cpp \
         data/status/_vtable_attack_cases_20260925/a1.cpp \
         data/status/_vtable_attack_cases_20260925/a2.cpp \
         data/status/_vtable_attack_cases_20260925/a3.cpp \
         data/status/_vtable_attack_cases_20260925/a4.cpp ; do
  n=$(basename $f .cpp)
  tools/wine_cl.sh /c /nologo /Od /GR /I$INC /Fo/tmp/vtso/$n.obj $f
  python3 tools/coff_vtable.py /tmp/vtso/$n.obj
done
# 本任务补充探针（源码见附录 A；存 /tmp，需按附录重建）
tools/wine_cl.sh /c /nologo /Od /GR /I$INC /Fo/tmp/vtso/syn_probe.obj  /tmp/vtso/syn_probe.cpp
tools/wine_cl.sh /c /nologo /Od /GR /I$INC /Fo/tmp/vtso/syn_probe2.obj /tmp/vtso/syn_probe2.cpp
python3 tools/coff_vtable.py /tmp/vtso/syn_probe.obj
python3 tools/coff_vtable.py /tmp/vtso/syn_probe2.obj
```

### 附录 A：补充探针源码与原始输出（2026-09-25 实测）

`syn_probe.cpp`（澄清合成槽"落声明位"语义 + 覆写打包细节）：

```cpp
struct P1 { virtual void o(); virtual ~P1(); virtual void o(int); };
void P1::o() {} P1::~P1() {} void P1::o(int) {}
struct P2 { virtual void o() const; virtual ~P2(); virtual void o(int); };
void P2::o() const {} P2::~P2() {} void P2::o(int) {}
struct P2b { virtual void o(); virtual void o(int); virtual ~P2b(); virtual void o(double); };
void P2b::o() {} void P2b::o(int) {} P2b::~P2b() {} void P2b::o(double) {}
struct B5 { virtual void a(); };
void B5::a() {}
struct D5 : B5 { virtual void o(); virtual ~D5(); virtual void o(int); };
void D5::o() {} D5::~D5() {} void D5::o(int) {}
struct B6 { virtual void a(); };
void B6::a() {}
struct D6 : B6 { virtual void x(); virtual void y(int); virtual void z(); virtual void y(double); };
void D6::x() {} void D6::y(int) {} void D6::z() {} void D6::y(double) {}
struct B7 { virtual ~B7(); virtual void f(); };
B7::~B7() {} void B7::f() {}
struct D7 : B7 { virtual ~D7(); virtual void g(); };
D7::~D7() {} void D7::g() {}
struct B8 { virtual void f(); virtual ~B8(); virtual void h(); };
void B8::f() {} B8::~B8() {} void B8::h() {}
struct D8 : B8 { virtual ~D8(); virtual void g(); };
D8::~D8() {} void D8::g() {}
struct B9 { virtual void o(int); };
void B9::o(int) {}
struct D9 : B9 { virtual void o(char*); virtual void o(int); virtual void o(short); };
void D9::o(char*) {} void D9::o(int) {} void D9::o(short) {}
int main() { P1 a; P2 b; P2b c; D5 d; D6 e; D7 f; D8 g; D9 h; return 0; }
```

`syn_probe2.cpp`（D1 判别样本）：

```cpp
struct BA { virtual void o(int); };
void BA::o(int) {}
struct DA : BA { virtual void o(int); virtual void z(); virtual void o(char*); };
void DA::o(int) {} void DA::z() {} void DA::o(char*) {}
struct BB { virtual void w(); };
void BB::w() {}
struct DB : BB { virtual void z(); virtual void o(int); virtual void y(); virtual void o(char*); };
void DB::z() {} void DB::o(int) {} void DB::y() {} void DB::o(char*) {}
int main() { DA a; DB b; return 0; }
```

原始输出（`python3 tools/coff_vtable.py …`，mangling 速查：`X`=void() `H`=int `N`=double
`D`=char `F`=short `M`=float `PAD`=char* `UBEXXZ`=o() const `??_E`=deleting dtor）：

```
syn_probe.obj
  ??_7B5@@6B@   [0] ?a@B5@@UAEXXZ
  ??_7B6@@6B@   [0] ?a@B6@@UAEXXZ
  ??_7B7@@6B@   [0] ??_EB7@@UAEPAXI@Z   [1] ?f@B7@@UAEXXZ
  ??_7B8@@6B@   [0] ?f@B8@@UAEXXZ   [1] ??_EB8@@UAEPAXI@Z   [2] ?h@B8@@UAEXXZ
  ??_7B9@@6B@   [0] ?o@B9@@UAEXH@Z
  ??_7D5@@6B@   [0] ?a@B5@@UAEXXZ   [1] ?o@D5@@UAEXH@Z   [2] ?o@D5@@UAEXXZ   [3] ??_ED5@@UAEPAXI@Z
  ??_7D6@@6B@   [0] ?a@B6@@UAEXXZ   [1] ?x@D6@@UAEXXZ   [2] ?y@D6@@UAEXN@Z   [3] ?y@D6@@UAEXH@Z   [4] ?z@D6@@UAEXXZ
  ??_7D7@@6B@   [0] ??_ED7@@UAEPAXI@Z   [1] ?f@B7@@UAEXXZ   [2] ?g@D7@@UAEXXZ
  ??_7D8@@6B@   [0] ?f@B8@@UAEXXZ   [1] ??_ED8@@UAEPAXI@Z   [2] ?h@B8@@UAEXXZ   [3] ?g@D8@@UAEXXZ
  ??_7D9@@6B@   [0] ?o@D9@@UAEXH@Z   [1] ?o@D9@@UAEXF@Z   [2] ?o@D9@@UAEXPAD@Z
  ??_7P1@@6B@   [0] ?o@P1@@UAEXH@Z   [1] ?o@P1@@UAEXXZ   [2] ??_EP1@@UAEPAXI@Z
  ??_7P2@@6B@   [0] ?o@P2@@UAEXH@Z   [1] ?o@P2@@UBEXXZ   [2] ??_EP2@@UAEPAXI@Z
  ??_7P2b@@6B@  [0] ?o@P2b@@UAEXN@Z  [1] ?o@P2b@@UAEXH@Z  [2] ?o@P2b@@UAEXXZ  [3] ??_EP2b@@UAEPAXI@Z
syn_probe2.obj
  ??_7BA@@6B@   [0] ?o@BA@@UAEXH@Z
  ??_7BB@@6B@   [0] ?w@BB@@UAEXXZ
  ??_7DA@@6B@   [0] ?o@DA@@UAEXH@Z   [1] ?o@DA@@UAEXPAD@Z   [2] ?z@DA@@UAEXXZ
  ??_7DB@@6B@   [0] ?w@BB@@UAEXXZ   [1] ?z@DB@@UAEXXZ   [2] ?o@DB@@UAEXPAD@Z   [3] ?o@DB@@UAEXH@Z   [4] ?y@DB@@UAEXXZ
```

## 6. 顾虑（concerns）

1. **"合成槽落声明位"按字面实现会被实测证伪**（P1/P2b）：字面下标钉死 ⇒ 错槽序。已按实测改为
   「单槽组按声明秩定组位」并在模块 docstring/测试注释中写明。**Task 5 的校验文案需采用同一语义**，
   避免校验器把正确槽序判死。
2. **打包细节 D1（覆写参与打包后摘除）是三条主规则之外的必要补充**——简报未提，但 DA 判别样本
   实测如此；已在规则文档中显式化。若后续任务按"只打包新增声明"实现共享逻辑会错槽。
3. **虚继承视图合成明确不支持**（NotImplementedError）：B-1..B-4 缺口归属 Task 2/5/6。当前只对
   **非虚**继承实测（vt2/vt3 平铺 MI）；嵌套 MI（新增段落"最左链首视图"）是**外推假设**，未实测。
4. **pytest 在本环境不可用**（环境自带 pytest 5.4.1.dev + py3.10 rewrite 崩溃，既有测试同样崩）；
   按仓库惯例 `python3 tests/<file>.py` 直跑 35/35。CI 若要 pytest 需先修环境。
5. **补充金样本（P1/P2/P2b/D5/D6/D7/D8/D9/DA/DB）不在三个既有 README 中**，源自本任务新探针
   （源码+原始输出见附录 A，tests 内联硬编码 expected）。建议把附录 A 并入
   `_vtable_abi_probe_20260925/README.md`（该目录自述"可作回归金样本"），或以本报告为唯一出处。
6. 视图标签是**诊断用**链根类名（对应 `??_7D@@6B<根>@@@` 的 `<根>`），未与 Task 6 的符号归约
   对接；虚继承下单表的符号形态（`??_7DV@@6B@`）与标签不一致，Task 6 对接时勿把标签当符号身份。

---

## 7. 评审发现项修复记录（2026-09-25，补充金样本探针源码落盘）

**发现项**：10 个补充金样本（P1/P2/P2b/D5/D6/D7/D8/D9/DA/DB）的探针源码仅存于本报告附录 A（`.superpowers/` 被 .gitignore 排除）与 `/tmp`，不可持久化验证。

**覆盖测试文件**：
- `tests/test_vtable_slot_order.py`（35 条金样本测试，其中 P1/P2/P2b/D5–D9 对应 `test_syn_*` 系列、DA/DB 对应 `test_d1_*` / `test_p10_p11_*` 系列的 inline 硬编码 expected）
- 被测实现 `tools/vtable_slot_order.py`（本次未改动）

**落盘文件**（新增，与 `/tmp/vtso` 原件逐行一致、含探针注释；已核对与附录 A 代码块 normalized-完全一致）：
- `data/status/_vtable_abi_probe_20260925/syn_probe.cpp` —— P1/P2/P2b + B5/D5 + B6/D6 + B7/D7 + B8/D8 + B9/D9
- `data/status/_vtable_abi_probe_20260925/syn_probe2.cpp` —— BA/DA + BB/DB（D1 判别样本）

附录 A 中**没有** P1/P2/P2b/D5–D9/DA/DB 的独立 .cpp 源码（全部内联在上述两个探针文件里），故无需额外落盘。

**所运行命令及输出**：

```sh
$ python3 tests/test_vtable_slot_order.py
  PASS test_a1_new_overloads_form_own_segment_never_join_base_group
  ... （35 行 PASS）
  PASS test_vt3_one_decl_replaces_slots_in_both_views
Results: 35 passed, 0 failed, 0 skipped
# EXIT=0  —— 35/35 仍通过 ✓
```

```sh
# 持久化验证：从落盘路径（非 /tmp 源）重新编译并比对附录 A 原始输出
$ INC=tools/compilers/msvc6.0/Include
$ tools/wine_cl.sh /c /nologo /Od /GR /I$INC /Fo/tmp/vtso_fix/syn_probe.obj \
    data/status/_vtable_abi_probe_20260925/syn_probe.cpp
$ tools/wine_cl.sh /c /nologo /Od /GR /I$INC /Fo/tmp/vtso_fix/syn_probe2.obj \
    data/status/_vtable_abi_probe_20260925/syn_probe2.cpp
$ python3 tools/coff_vtable.py /tmp/vtso_fix/{syn_probe,syn_probe2}.obj   # 槽序逐条比对附录 A
expected vtables: 17  actual: 17
ALL SLOTS MATCH Appendix A: True
# ⇒ 17 张 vtable 全部槽序与附录 A 原始输出逐槽一致 ✓，样本自此可脱离 /tmp 与本报告复现
```

**提交**：`data/status/_vtable_abi_probe_20260925/syn_probe.cpp`、`syn_probe2.cpp`（git add + commit）。

**遗留（不在本发现项范围，供后续任务参考）**：
- `_vtable_abi_probe_20260925/` / `_vtable_advprobe_20260925/` / `_vtable_attack_cases_20260925/` 三个金样本目录
  整体仍是 **git 未跟踪**（含各自 README 与 vt2/vt3/vt5–vt7、adv1–adv7、a1–w2 等既有源），
  且 `_vtable_abi_probe_20260925/README.md` 自述"本目录为未跟踪草稿"。本次仅按发现项落盘补充样本 2 文件；
  既有 9+ 源是否入库需评审/后续任务裁定（若入库应同步修订该 README 的"未跟踪草稿"措辞）。
