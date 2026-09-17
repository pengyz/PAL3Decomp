# 修复：`->std::string::_Tidy()` 非法形态（本会话自引入的回归）

**日期**：2026-09-17 · 触发：调查陈旧基线报出的 3 个"新错误"文件

---

## 1. 回归是什么、谁引入的

`regression_detector` 相对 2026-09-15 基线报出 `pal3/src/GameBase/Config.cpp`
错误数 8 → **14**，新增：
```
C2039 - 'std' : is not a member of 'GRPinput'
C2653 - 'std' : is not a class or namespace name
```
定位到生成物里的非法 C++：
```cpp
(((GRPinput *)this))->std::string::_Split();
(((std *)v6))->std::string::_Eos();
```
`p->std::string::_Split()` 在 MSVC6 下非法（它把 `->std` 当成成员查找）。

**引入者 = 本会话第 4 项落地 `75f3b8760`（归属门禁归一化）**。当时的量测是
"ok+3、总错误 −150、matched+7"（净赢），但它**同时**在这类站点上产生了非法形态。
全量统计：生成物里 `->A::B::m(` 形态共 **75 处**
（`std::string::_Tidy` 36、`_Eos` 11、`_Split` 10、`~string` 3、`_Freeze` 3、
`_Grow` 1、`std::codecvt_base::do_always_noconv` 11）。

## 2. 两个根因（不是一个）

1. **只有 3 个 emit 点加了限定符处理**，而 `ast_transform.py` 里产
   `->Cls::method` 的格式串共有 ~12 处（469/531/542/582/614/630/722/741/751/763/775/782）。
2. **更深的一层**：tree-sitter 对 `std::string::_Eos(...)` 给的是**嵌套**
   `qualified_identifier` —— `scope='std'`、`name='string::_Eos'`。
   代码只取一层 ⇒ `class_name='std'` ⇒ 不但限定符重复，**cast 类型也错了**
   （`((std *)v6)` 而不是 `((std::string *)v6)`）。

## 3. 修法（结构修 + 兜底）

`pipeline/gen/ast_transform.py`：
1. **摊平嵌套限定名**：循环下钻 `qualified_identifier`，把各层 scope 拼进
   `class_name`，`method_name` 取最内层名字 ⇒ `class_name='std::string'`、
   `method_name='_Eos'`。
2. `_qual = '' if '::' in class_name else class_name + '::'` —— 限定名时省略限定符、
   **保留 cast** ⇒ `((std::string *)v6)->_Eos()`。
3. **兜底归一化**（防下一个 emit 点再犯）：在 `transform_oop_calls` 输出处折叠
   `->(?:Ident::){2,}name(` → `->name(`。合法 C++ **绝不会**有 ≥2 段限定名跟在
   `->` 后；**单段** `p->Cls::m()` 是合法的、且是刻意保留的非虚调用形式，**不动**。

## 4. 验证（同轮实测）

| 指标 | before | after |
|---|---|---|
| 生成物里非法形态 `->A::B::m(` | **75** | **0** |
| `Config.cpp` 错误数 | 14 | **6** |
| `regression_detector --check` 的"新错误"文件数 | 3 | **2** |
| `probe` s2 ok | 61/202 | 61/202（Δ0）|
| `match` L1 / matched | 17 / 191-218 | 17 / 191-218（Δ0）|

`Config.cpp` 现已 **6 < 基线 8**，即相对那条陈旧基线它是**改善**，不再被标记。

**诚实结论：去掉 8 个错误、消除 75 处非法形态；`ok`/`L1` 不变** —— 因为
`Config.cpp` 仍余 6 个错误、没有翻成 pass，所以 `ok` 不动。

## 5. 仍未解释的 2 个回归（**因此不刷新基线**）

```
pal3/src/globals.cpp   58 → 96   C2373: 'aUiCombatPointe' / 'aCbdataFlexcamD'
                                 redefinition; different type modifiers
pal3/src/Data/PAL_GDB.cpp 33 → 52  C2065: 'v20' : undeclared identifier
                                 C2653: '_inline_RoleAtt_Remark' is not a class or namespace name
```
两者在 `data/status/*.md`、`docs/knowledge/*.md` 里**都没有记录**，且早于今天
所有改动（同轮 `probe_census` 已含它们）。工具自身的指引是"确认回归被理解后再
刷新基线"—— **未理解，故不刷新**，留给下一轮。

## 6. 顺带修掉的门禁缺陷：`annotation_diff` 不比较 `methods`

**真因**：`compare_struct` 只比较 `binary_size` 与 `known_members`，
**`methods`（函数归属）从不比较**。于是把 `UIWnd::GetWidth/GetHeight/GetPosition`
迁到 `UIProgressBar` 之后，它仍报「变更结构体数量: 0 / verdict: clean」，
而 `git status` 明确显示两个文件已修改。**一个报 clean 的门禁比没有门禁更危险**
（而归属迁移正是本项目最主要的改动类型）。

**修法**：不逐个补字段（那样下一个新字段还会被静默忽略），而是
**白名单（`name`/`known_members`/`binary_size`）之外的顶层字段全部比较**，
dict 字段再按键细化，报告里能看出是哪个 VA / 哪个基类变了。
新增 `tools/test_annotation_diff.py`（12 用例）：方法增/删/改、`base_class` 变更、
`vtables` 变更、**未来新字段**、以及 `compare_struct` 必须把 methods 变更并进结果。

端到端复现：临时移除 `UIProgressBar.methods['0x0043FDC0']` → 门禁报
`变更结构体数量: 1 / verdict: changed` 并打印 `- methods[0x0043FDC0] ...`（已还原）。

## 7. 勘误：我上一份文档对 `probe` 的第 3 条指控是错的

`_cleanup_landing_uiwnd_3methods.md` §5 第 3 条称
「`probe` 把'错误数下降'打成'回归'，语义反了」——**不成立**。
读码确认：判定是 `has_regression = summary["new_failures"] > 0 or summary["new_errors"] > 0`，
即**由（陈旧的）基线驱动**；`📈 错误数量变化` 里的 `↓` 只是附带信息，不是判据。
真实缺陷只有一个：**基线陈旧**（见 §5）。据此，该条应从"独立缺陷"降为
"陈旧基线的症状"。

## 8. 复现

```bash
grep -rhoE "\->[A-Za-z_]\w*::[A-Za-z_]\w*::[A-Za-z_~]\w*\(" pal3/src | wc -l   # 应为 0
python3 -m unittest tools.test_annotation_diff tools.test_scan_misattribution
python3 tools/regression_detector.py --check --format text
python3 pipeline/cli.py probe && python3 pipeline/cli.py match
```