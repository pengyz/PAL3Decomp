---
name: gotcha-local-pytest-collect-crashes-use-self-runner
description: 本机 python3 -m pytest 在任何文件上都在 collect 阶段崩（TypeError: required field "lineno" missing from alias），根因是 sys.path 混入了 aide 的 pytest dev 构建；因此仓内测试文件一律自带 __main__ runner，不依赖 pytest fixture
type: gotcha
created: 2026-09-20
updated: 2026-09-20
status: active
sources: [session-2026-09-20]
---

# gotcha：本机 pytest 不可用 ⇒ 测试文件自带 `__main__` runner

## 现象（2026-09-20 实测）

```
$ python3 -m pytest tests/xxx.py
TypeError: required field "lineno" missing from alias        # collect 阶段就崩
```
根因：`sys.path` 里混入了 `/home/peng/workspace/aide/benchmarks/.../pytest-dev__pytest-7432`
的 **dev 构建**，其 AST 处理与 Python 3.10 不兼容 ✗ ⇒ **pytest 的 `monkeypatch` 等 fixture 在本机不可执行** ✗。

## 规则（本仓约定）

1. **每个测试文件自带 `__main__` runner** ✓：遍历本模块的 `test_*` 函数、按签名注入
   `tmp_path` / `monkeypatch` 之类的**替身**（如轻量 `_MiniPatch` ✓），最后打印
   `Results: N passed, M failed[, K skipped]` 并 `sys.exit(1 if fail else 0)` ✓
2. **不要依赖 pytest 独有的能力** ✓（fixture、参数化、插件 ✓）
3. **runner 要捕获 `Exception` 而不只是 `AssertionError`** ✓ —— 契约被破坏时常表现为
   `AttributeError`/`TypeError` ✓；若只捕获 `AssertionError`，一个用例崩掉会**隐藏后续用例结果** ✗
4. **缺输入时应诚实 SKIP** ✓（用哨兵值），不要静默当 PASS ✗
5. **运行方式写进测试文件自身**（`python3 tests/xxx.py` ✓），不要写 `pytest tests/xxx.py` ✗
