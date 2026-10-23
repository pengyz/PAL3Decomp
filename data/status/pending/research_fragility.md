# 管线脆弱性盘点

> 2026-10-23 只读调研，未改任何产品文件。全部数字为实测（grep + ast 统计）。

## 分支/例外统计

代码规模：pipeline/ 37,844 行 Python；gen/ 非测试 17,374 行 + 29 个 test 文件。

| 文件 | 行数 | if | elif/else | if族合计 | 循环 | try | 名特判 |
|---|---|---|---|---|---|---|---|
| emit_headers.py | 4,454 | 581 | 35/61 | 677 | 161 | 82 | 23 |
| emit_cpp.py | 867 | 115 | 3/12 | 130 | 40 | 4 | 3 |
| ast_transform.py | 2,305 | 229 | 25/25 | 279 | 93 | 44 | 27 |
| **三文件** | **7,626** | **925** | **63/98** | **1,086** | **294** | **130** | **53** |

- 分支密度：emit_headers **每 6.6 行 1 个分支**（677/4,454），极高。
- 全 gen/ 硬编码名特判 **300 处**（stage4 151·stage3 50·ast_transform 27·emit_headers 23·stage5 18·emit_cpp 3）。
- 大写特例表 pipeline/ 共 **221 个**（stage4 45·stage5 31·emit_headers 30·stage3 22）。
- 例外类注释（exception/hack/特例/legacy/fallback）**313 条**。
- 巨型函数：`generate_header` **1,720 行**（占 emit_headers 39%）、`transform_oop_calls` 505 行、`process_node` 458 行、`_collect_token_edits` 342 行。

## 相互作用

1. **双副本表分叉（已实证）**：`_GB_REF_PARAM_FUNCS` 在 stage3/stage5 各一份——实测 stage3 29 键 / stage5 34 键 / 交集 29 / **仅 stage5 多 5 键**（GetBlend、SetBlend、PointWorldToScr、RightMultiply、gbOBBox::GetAABBox）。典型"修一漏一"面（CLAUDE.md 记 6 键，本次实测 5）。
2. **表内双定义**：emit_headers `_MACRO_CONFLICTS`（10 个 WinAPI 名）在 :2822 与 :2929 两处内联重复，改一漏一即宏守卫不一致。
3. **注解读点例外**：声明走 `annotation_view` 单一读点，但仍剩 **3 处直读**（emit_headers:3259 `globals.json`·ast_transform:336-342 `structs/*.json`·stage3_cleanup:107-110 `structs/<Cls>.json`）。
4. **stage 顺序耦合**：stage3 依赖 stage2 输出形态，stage5 文本补丁叠在 stage4 AST 之后；改 stage3 特判常需同步 stage5（见 1）。仅 test_hook_order.py 锁顺序。
5. **度量盲区放大交互风险**：C1003 截断单元 2 个掩盖错误变化；L1 重定位 don't-care 覆盖 27.65% 字节（隐藏差异 19.24%）⇒ 分支改动的真实影响可能被测量掩盖。

## 可维护性评估

- **改动波及面**：改 1 个名特判理论上影响全部 ~209 编译单元输出，只能靠 `codegen all → match` 全量回归确认；300 个特判**绝大多数无专属单测**（29 个 test 锁机制不锁具体名单）。
- **读代码成本**：1,720 行单函数内任一改动需理解整体布局；6.6 行/分支的密度使控制流交织严重。
- **护栏有效但不完美**：loop --expect / compile_regression / match / link_probe 四道门能捕获回退，但盲区与双副本分叉使"改了没坏"置信度打折。
- **本性 vs 结构债**：MSVC6 + Hex-Rays 语法缺口 + 字节匹配目标本身例外密集（CRT 边界/vtable/模板特化），约半数分支属**问题本性**；双副本表、3 处直读、巨型函数属**可收敛的结构债**。

## 结论（脆弱性程度）

**中高（结构脆弱，护栏尚可）**。用户"到处充满例外和分支"的判断**成立**：三核心文件 1,086 个分支、全 gen 300 个名特判、221 个特例表、313 条例外注释。但脆弱性不均匀分布——集中在①双副本表（实证分叉 5 键）②1,720 行巨型函数 ③3 处直读违规 ④stage 顺序耦合。约半数分支是字节匹配目标的固有代价，无法消除。**优先收敛三项**：并表 `_GB_REF_PARAM_FUNCS`、拆 `generate_header`、清 3 处直读——做完可把结构性脆弱降到中等。
