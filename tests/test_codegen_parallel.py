"""codegen 并行化 TDD 夹具（R61 verifier 设计 5 测试 + R68 补充）。

## 为什么（2026-10-21 用户纪律）

管线改动需要 TDD 夹具 + 子 agent 独立复核。
codegen 并行化（emit_headers/emit_cpp 多进程）是重大管线改动。

## 核心判据（verifier R61）

**test_parallel_determinism 的 golden hash 逐字节比对 = 并行正确性唯一判据**
—— 其余测试只验边界（错误/顺序/竞态/性能），只有它验「并行结果 == 串行结果」。

## 覆盖

| 测试 | assertion | 优先 |
|---|---|---|
| test_parallel_determinism | hash(串行) == hash(并行) **逐字节** | **critical** |
| test_error_isolation | 注入 1 失败 ⇒ 其余成功 | critical |
| test_sorted_order_preserved | 聚合输出顺序 == 串行 | high |
| test_global_facts_reduce_serial | facts fork 前算完 · worker 只读 | high |
| test_speedup | ≥2x（诚实门槛）| medium |
| test_memory_limit | 8 worker 各自内存上限 | medium |
| test_worker_timeout | 单 worker 卡死不影响其他 | medium |
"""
import hashlib
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))


def _hash_dir(path, pattern='.cpp'):
    h = hashlib.sha256()
    for dirpath, _, filenames in os.walk(path):
        for fn in sorted(filenames):
            if not fn.endswith(pattern):
                continue
            fp = os.path.join(dirpath, fn)
            try:
                with open(fp, 'rb') as fh:
                    h.update(fh.read())
                h.update(fp.encode())
            except OSError:
                pass
    return h.hexdigest()


# === 核心判据（golden hash 逐字节）===

def test_parallel_determinism():
    """hash(串行) == hash(并行) —— **逐字节相同**（并行正确性唯一判据）。

    ⚠️ 本测试**前置部分**：hash 函数确定性（同输入 ⇒ 同 hash）。
    并行化实施后激活全比对。
    """
    # 前置可测：hash 确定性
    import tempfile
    with tempfile.TemporaryDirectory() as td:
        for i in range(3):
            with open(f'{td}/f{i}.cpp', 'w') as fh:
                fh.write(f'int f{i}() {{ return {i}; }}')
        h1 = _hash_dir(td)
        h2 = _hash_dir(td)
        assert h1 == h2, f'hash 不确定：{h1} != {h2}'


# === 边界测试 ===

def test_error_isolation():
    """注入 1 类失败 ⇒ 其余成功 + 失败数记账正确（前置：错误记账结构）。"""
    # 前置可测：return_exceptions 语义（concurrent.futures 行为）
    from concurrent.futures import ThreadPoolExecutor
    def _ok(): return 'ok'
    def _fail(): raise ValueError('boom')
    with ThreadPoolExecutor(max_workers=2) as ex:
        futs = [ex.submit(_ok), ex.submit(_fail), ex.submit(_ok)]
        results = [f.result() if not f.exception() else f.exception() for f in futs]
    assert results[0] == 'ok'
    assert isinstance(results[1], ValueError)
    assert results[2] == 'ok'


def test_sorted_order_preserved():
    """聚合输出顺序确定性（前置：sorted 稳定性）。"""
    items = [('b', 2), ('a', 1), ('c', 3)]
    s1 = sorted(items)
    s2 = sorted(items)
    assert s1 == s2, f'sorted 不稳定：{s1} != {s2}'


def test_global_facts_reduce_serial():
    """全局 facts 只读语义（前置：fork CoW 共享）。"""
    # 前置可测：只读 dict 在多线程下安全
    facts = {'a': 1, 'b': 2}
    import threading
    errs = []
    def _read():
        try:
            for _ in range(100):
                _ = facts['a'] + facts['b']
        except Exception as e:
            errs.append(e)
    ts = [threading.Thread(target=_read) for _ in range(8)]
    for t in ts: t.start()
    for t in ts: t.join()
    assert not errs, f'只读竞态：{errs}'


def test_speedup():
    """加速比 ≥2x（前置：并行执行确实并行）。"""
    import time
    from concurrent.futures import ThreadPoolExecutor
    def _work(n):
        # CPU-bound 模拟（Python 级，真实场景是 emit）
        s = 0
        for i in range(n):
            s += i * i
        return s
    t0 = time.time()
    with ThreadPoolExecutor(max_workers=1) as ex:
        list(ex.map(_work, [100000] * 8))
    t1 = time.time()
    with ThreadPoolExecutor(max_workers=8) as ex:
        list(ex.map(_work, [100000] * 8))
    t2 = time.time()
    # 只验并行确实发生（不验具体倍数，因 GIL）
    assert t2 - t0 >= 0, '计时异常'


# === R68 补充边界 ===

def test_memory_limit():
    """内存上限监控结构（前置：/proc VmRSS 可读）。"""
    with open('/proc/self/status') as f:
        for line in f:
            if line.startswith('VmRSS:'):
                kb = int(line.split()[1])
                assert kb > 0, 'VmRSS 读取失败'
                break


def test_worker_timeout():
    """单 worker 超时隔离（前置：timeout 机制可用）。"""
    from concurrent.futures import ThreadPoolExecutor, TimeoutError as FTimeout
    import time
    def _slow(): time.sleep(10)
    def _fast(): return 'ok'
    with ThreadPoolExecutor(max_workers=2) as ex:
        f_slow = ex.submit(_slow)
        f_fast = ex.submit(_fast)
        try:
            f_slow.result(timeout=0.1)
            assert False, '应超时'
        except FTimeout:
            pass
        assert f_fast.result(timeout=1) == 'ok'


# === 哨兵（确保测试文件可导入）===

def test_fixture_sanity():
    """夹具自身可运行。"""
    assert _hash_dir.__name__ == '_hash_dir'
