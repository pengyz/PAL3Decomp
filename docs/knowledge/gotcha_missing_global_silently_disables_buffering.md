---
name: gotcha-missing-global-silently-disables-buffering
description: 函数内给模块级名赋值却没写 global，只会建一个局部名——"两阶段缓冲落盘"于是根本不存在，而测试因为拒绝发生在校验阶段而"通过"
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：漏一个 `global` ⇒ "两阶段全或无"根本不存在，而测试**通过**了

## 现象

我在 `tools/apply_annotation_batch.py` 里做"两阶段落盘"：先缓冲、无拒绝才 flush。

```python
    global _DRY_RUN
    _DRY_RUN = bool(...)
    _BUFFER = {} if not _DRY_RUN else None      # ✗ 没有 global _BUFFER
```
`main()` 内只声明了 `global _DRY_RUN` ⇒ `_BUFFER = {}` **只建了一个局部名** ✗ ⇒
`save_ann()` 读到的**模块级 `_BUFFER` 恒为 `None`** ⇒ **逐条直写** ✗。

**我的"成对行为验证"当时是绿色的** ✓：一个含拒绝的批 ⇒ `exit=1` + 零落盘 ✓ ——
但那次的拒绝发生在**校验阶段**（写之前 ✓），**根本没走到写入阶段** ✗
⇒ 测试通过的是**另一条路径**（同族：[[page:gotcha-tests-must-assert-contract-not-status-quo]]）。

**由独立复核者反汇编发现**（1×STORE_FAST / 0×STORE_GLOBAL），并实测："第 1 条已写、
第 2 条被拒，仍打印 `[flush] 统一落盘 0 个文件（两阶段 ✓）` 且 **rc=0**" ✗。

## 规则

- **任何"先缓冲后落盘/延迟提交"的安全性，都必须把守卫放在唯一的落盘出口上** ✓
  （本项目里 `--dry-run` 之所以真的有效，正是因为它守住的是 `save_ann` 这个**单点** ✓）；
  分散在分支里的检查等于没有 ✗。
- **写"全或无"的测试，必须让拒绝发生在被保护的那一段** ✓（本例应构造"第 1 条合法 + 第 2 条非法"，
  并断言**第 1 条也没落盘** ✓）。
- 修完后要有**非零退出**：写入阶段的拒绝也必须让进程失败 ✓。
- 自查手段：`python -c "import ast; ..."` 检查函数内 `global` 声明是否覆盖所有被赋值的模块级名 ✓。
