---
name: windows-gbk-stdio-unicode-crash
description: Windows 下 Python stdio/文件默认 GBK ⇒ print ⚠/⇒、ensure_ascii=False 写盘、text=True 捕获三处连环崩；单源修复 pipeline/utf8_stdio.py，registry 环境变量/profile/repo 级 sitecustomize 三条全局路实测无效
type: gotcha
created: 2026-11-03
sources: [session-2026-11-03 编码修复]
---

Windows（Python 3.12，stdio 编码=locale=gbk）下含 ⚠/✓/⇒/❌ 的输出在三个位置连环崩：`print`（GBK 不可编码）、`json.dump(ensure_ascii=False)` 写入未指定 `encoding` 的 `open('w')`（U+FFFD 等）、`subprocess.run(text=True)` 捕获 UTF-8 子进程输出按 GBK 严格解码（异常被吞后表现为"内容读不出"）。

**为什么：** 本仓产物/注解是 UTF-8，而 Windows Python 的 stdio 与 `open()` 文本默认编码 = gbk——同一根因三个面（实测 `cli.py status` 崩于 preflight 打印、`error_classifier` 崩于 report 落盘、`annotation_diff`/`verify_fix` 的 `git show` 读内容全灭）。修复=单源 `pipeline/utf8_stdio.py::force_utf8_stdio()`（重配 stdio UTF-8 + `PYTHONIOENCODING` 给子进程传播），11 个入口按标准块接线；`compile_regression.py` F52-bis 的内联块（第 133 轮同坑）已收敛。2026-11-03 实测**无效**的三条全局路：repo 根 `sitecustomize.py`（启动早于脚本目录入 path）、registry 用户环境变量（不穿透进程树 env 块）、pwsh `$PROFILE`（harness `-NoProfile`）。

**何时使用：** 在 Windows 跑 pipeline/tools 前；新增入口脚本时照抄标准块接 `force_utf8_stdio()`；遇"内容读不出/写不出"先查编码再怀疑数据。刻意未修：`open()` 全局默认与 `probe_compile.py:115` 写合成源码（GBK 是 MSVC6 的正确输入语义，见 gotcha_gbk_comment_trailing_backslash_eats_next_line.md）。
