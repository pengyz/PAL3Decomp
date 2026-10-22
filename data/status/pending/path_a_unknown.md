# Path A 深化：unknown 30.9% 归因

> ⚠️ **数据时效警告（最重要）**：本次分析基于 `probe_census.json`（生成于 **14:58**）。
> 但分析时（16:02）检测到 **`codegen all --skip-probe` 正在运行**（PID 3481319，15:59 起），
> 正在重写 `pal3/src`（`CCBControl.cpp` mtime 16:01、`tagCmdData.h`/`tagCmdDataDestRoleView.h` 16:00）
> —— 均**晚于** census。⇒ **"unknown 29 (30.9%)" 是陈旧缓存快照，本次 codegen 完成并重跑 probe 后会变动**。
> 下列归因对"错误码→根因层"的判断是**耐久的**；但具体计数与文件清单须以 codegen 后的新 census 为准。

## 错误码分布
`unknown` 是 error_classifier **RULES 表未覆盖**的兜底类（非真"神秘"）。29 个 dominant-unknown 文件里
共 109 条 unknown 错误；全 94 文件合计 294 条。头部错误码（含真实 msg）：

| 错误码 | 全量 | 采样 msg 证据 | 归因层 |
|---|---|---|---|
| C2653 | 55 | `'CEffObj' : is not a class or namespace name` | annotation |
| **C2208** | **42** | `'class tagCmdDataDestRoleView' : no members defined using this type` | annotation（单点）|
| C2675 | 20 | `unary '!' : 'class CCBTaskSlot' does not define this operator` | annotation |
| C2027 | 20 | `use of undefined type '_Console'` | annotation |
| C2673 | 19 | `'GetBBox' : global functions do not have 'this' pointers` | annotation（归属）|
| C2036 | 15 | `'void *' : unknown size` | annotation |
| C2248 | 13 | `'do_always_noconv' : cannot access protected member 'std::codecvt_base'` | codegen（CRT 边界）|
| C2446 | 13 | `'!=' : no conversion from 'char *' to 'class PalScript *'` | annotation |
| C2451 | 12 | `conditional expression of type 'class CCBTaskSlot' is illegal` | annotation |
| C2117 | 11 | `' %s' : array bounds overflow`（globals.cpp） | annotation |
| C2784 | 6 | `could not deduce std::basic_string<...>`（CScreenMode.cpp） | **hexrays** |
| C2094 | 3 | `label '_flt_45_0' was undefined`（ScriptSystem.cpp） | codegen |

## 归因明细（采样）
按错误码+文件逐一归因，rollup（29 文件的 109 条 unknown）：
**annotation 86 / codegen 17 / hexrays 5 / unclear 1**（全量 294 条：81.3% / 8.5% / 3.7% / 6.5%）。
⇒ **unknown 的本质 ≈ annotation 层欠账**（缺类/缺成员/缺类型/归属/点性），不是新根因类。

采样裁决：
- **C2208（42 条 / 20 个文件，最大簇）** —— 单一共享根因：`tagCmdData.h:16` 的
  `tagCmdDataDestRoleView m_destRoleView;` 按值成员（该 struct 由 `_inline_tagCmdData_::$80FB...` **去 inline 化**而来，
  见 `data/annotations/structs/tagCmdDataDestRoleView.json`）。**修一处清 20 文件**。
  ⚠️ **诚实标注：确切触发机制 unclear** —— 单独 include `tagCmdData.h` 及最小 struct 复现（含 `_BYTE[7]+void*` pack(1)）
  **均未复现 C2208**；direct 编译 `CCBControl/Combat/CCBItemWindow` 也无 C2208。差异疑因 codegen 并发重写源码或
  include 链上下文（pack 状态/前置声明）；须 codegen 收敛后单点 probe 定谳。
- **C2675 + C2451（CCBTaskSlot/MiniGame3/String，共 32 条）** —— class 对象进 `!` / `?:` 布尔上下文
  ⇒ 原始几乎必是指针/标量，annotation 点性/类型错。归 **annotation_fix**（中置信，也可能 codegen 少解引用）。
- **C2673（gbOBBox.cpp 15 条 `GetBBox`）** —— 方法被当全局函数发（用 `this`）⇒ **函数归属 annotation**，高置信。
- **C2027（`_Console` 17 条）** —— 缺类型定义 ⇒ annotation 补 struct；若 `_Console` 是 Hex-Rays 虚构名则转 hexrays。
- **C2036（`void*` 15 条）** —— `void*` 需真实类型 ⇒ annotation。
- **C2248（std::codecvt_base 11 条）** —— 触 std 内部 ⇒ **codegen/CRT 边界**（非 annotation）。
- **C2784（std::basic_string 模板）** —— 真 **hexrays_limit**（模板），RULES 漏判。
- **C2094（`_flt_45_0` label）** —— codegen 常量/label 发射。
- **19 条 unclear**（C2259/C2665/C2146/C2296/C2491 等）：msg 证据不足，**判不了，留 unclear**。

## 修复优先级
1. **P0 · 重跑 probe 校准**（前置）：codegen all 收敛 → `apply→export` → `probe` → `error_classifier`。
   当前 unknown 基线不可直接驱动修复（陈旧 + C2208 不可复现）。
2. **P1 · C2208 单点**（`tagCmdDataDestRoleView`，预期清 ~20 文件 / 42 条）——先定谳机制（补前置声明/pack 归位）。
3. **P2 · annotation 批量欠账**：C2653 缺类、C2027 缺 `_Console`、C2036 `void*`、C2673 归属、C2675/C2451 点性 —— 合计 >150 条，
   与既有 annotation_fix 同类，随标注推进自然消解。
4. **P3 · codegen 层**：C2248 CRT 边界、C2094 label、C2668 重载歧义。
5. **P4 · hexrays_limit**：C2784 模板等（~11 条）——记录不修，与既有 hexrays_limit 合并。

## 结论
- **unknown 并非第四类根因**：81% 归 **annotation**，8% codegen，4% hexrays，6% unclear。
  分类器把它们归 unknown 只是 **RULES 表覆盖不全**（C2653/C2208/C2675/C2027 等头部码全无规则）。
- **最大单项 C2208 是单点共享根因**（去 inline struct 按值成员），但**当前不可复现**——
  根因是 **陈旧 census**（codegen 正在跑）还是 include 上下文，**判不了，须重跑后定谳**。
- **可修性**：annotation 类（P2，>150 条）随现有标注流程高 ROI 消解；C2208 单点高杠杆；
  hexrays 模板类不修。**未改任何产品文件**（本报告为只读分析）。
