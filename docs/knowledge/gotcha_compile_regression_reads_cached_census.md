---
name: gotcha-compile-regression-reads-cached-census
description: compile_regression.py 只读 data/status/probe_census.json，从不重新编译 ⇒ 在 codegen all 之后直接跑它，会拿上一轮的 census 报「✅ No regressions」，对刚刚生成的代码毫无约束力
type: gotcha
created: 2026-09-18
updated: 2026-09-18
status: active
sources: [session-2026-09-18]
---

**现象**：改完 codegen（stage5 的引用参数修复）后跑 `codegen all`，紧接着按 CLAUDE.md 的
「codegen all 后 → `python3 tools/compile_regression.py`」执行，输出：

```
Baseline S2: 61/204
Current S2: 61/202
✅ No regressions detected
Net change: 0 files
```

看起来"无回归"。但此时真实状态已经是 **63/202**（两个文件由 fail 转 ok）。
即：**它对刚生成的代码毫无约束力，而且方向是"报平安"**——最危险的那种失效
（若改动引入的是退化，它同样会安静地说"无回归"）。

**为什么**：`tools/compile_regression.py:16,23` 只做一件事——

```python
PROBE_FILE = PROJECT_ROOT / "data" / "status" / "probe_census.json"
...
if not PROBE_FILE.exists():
    print(f"Error: {PROBE_FILE} not found. Run probe_compile.py first.")
```

它**读缓存**，不调用编译。`data/status/probe_census.json` 是 `probe all` / `probe_compile.py`
的产物，只有当**有人跑过 probe** 时才与当前 `pal3/src` 对应。

**正确顺序**（CLAUDE.md 的检查点表缺了中间这一步）：

```
codegen all  →  probe all  →  compile_regression.py  →  error_classifier.py  →  match
                ^^^^^^^^^^ 必需，否则后面全在看旧数据
```

**判别信号**：`compile_regression.py` 打印的 `Current S2: N/202`（202 = 总单元数，与
`pal3/src` 文件数一致）如果和你刚观察到的文件数/ok 数不符，就是读了陈旧 census。
另一个信号是它报 `Baseline S2: 61/204` 而基线文件里写的是 `total: 202`——`204` 是它自己
按 `ok_files` 长度另行推算的口径，口径不一致本身就说明它是纯文本对账、不带编译。

**同类风险**：`data/status/baselines/latest.json` 由 `probe all` 自动刷新（`probe all` 的输出里有
`[Baseline] refreshing latest baseline...`），所以"回归检测基线"是被 probe 顺带推进的——
一次 `probe all` 会同时改掉**检测基准**，不能把它当作"只读一次现状"的操作。

**规避**：任何"改代码 → 验证"的循环里，`probe all` 是**代码生成与所有对账工具之间的唯一同步点**；
不要用 `compile_regression.py` 的输出去证明"刚生成的代码没退化"。
（本条与 `gotcha_measurement_bench_replicating_subject_logic.md` 附四"门禁盲区"同类。）