---
name: gotcha-measurement-bench-replicating-subject-logic
description: 离线测量台若自己复刻被测逻辑，会制造假象——captain 因此误判一处正确修复为「无效」
type: gotcha
created: 2026-09-15
updated: 2026-09-15
status: active
sources: [session-2026-09-15]
---

**现象**：为验证 VC6 mangler 的修复，写了离线测量台 `tools/mangler_bench.py`（复用 `/tmp/ua/*.obj` 的 56 个编译产物，避免每次占用 IDB 窗口重编）。测量台**自己复刻了一份 `compare_pal3.build_mangled_map`** 的逻辑。结果是：

- 在真实现里加了一处修复（从"name 本身已是 mangled 名"的 decomp 条目里解析类/方法名）后，
  **单测命中**（`mangle(...)` 产出与真实符号逐字符相同），
- 但**测量台显示 +0**，
- ⇒ captain 一度判定「该分支没用」，差点回滚一个**正确且有 +4 命中收益**的修复。

真因：测量台复刻的那份逻辑**没有同步这处修复**（它真的、独立地、复制了一份不含修复的代码）。

**为什么**：
离线测量台的价值来自"不占用稀缺资源（IDB 单写者窗口）就能高频复测"，代价是它必须**独立于管线**运行。
一旦它**复制**（而非**复用**）被测逻辑，两边就会漂移：管线改了、测量台没改，
测量台就变成"测量另一个程序"——**它测的不是你改的东西**。
这类假象特别危险，因为它**看起来是可信的负结果**（"我加了修复但指标没动"），
比崩溃更难发现，且会诱导人**回滚正确的修改**。

**何时使用 / 操作规程**：
- 写任何离线测量台/对比脚本时，**优先 `import` 复用被测的真实函数**（本例：
  `sys.path.insert` 后 `import compare_pal3 as cp; cp.build_mangled_map(idx)`），
  **不要复制**其逻辑。
- 若因依赖太重无法 import，则必须在测量台里显式标注"本文件复刻了 X 的逻辑，
  X 变更时**必须同步**"，并在每次改 X 后**用一个已知的正例校准测量台**
  （本例的正例是 `?PushOpen@AStarPathFinder@@QAEHPAUNODE@1@@Z`，单测必须 MATCH）。
- 判据顺序：**先单测（正例 MATCH）→ 再看测量台数字**。若单测 MATCH 而测量台不动，
  **先怀疑测量台**，不要怀疑修复。