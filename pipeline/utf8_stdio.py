"""stdio UTF-8 单源引导 —— Windows GBK 控制台 print 崩溃修复（多入口共用）。

病灶（2026-11-03 实测，Windows / Python 3.12.1）：

* 进程 stdout/stderr 编码 = locale = **gbk**（`python -c "print(sys.stdout.encoding)"` 实测）；
* 管线/工具输出含 ⚠(U+26A0)/✓/✗/⇒/❌ 等 GBK 不可编码字符 ⇒ ``print`` 抛
  ``UnicodeEncodeError`` 直接崩。实测两形态：``python pipeline/cli.py status`` 在
  ``preflight.render`` 的打印处崩；子进程工具打 ⚠ 同崩（rc=1，管道捕获时编码仍 gbk）。
* 同款坑的单点内联修复早已存在（``tools/compile_regression.py`` F52-bis，第 133 轮实测：
  报告已算完、最后一行 ``✅ No regressions detected`` 抛异常 ⇒ 门禁被误判"有退化"）。
  2026-11-03 按 D7（确定性下游工具分叉收敛）把该内联块收敛为本单源。

修复内容（``force_utf8_stdio()``，幂等、任何环境不抛异常）：

1. 本进程 stdout/stderr 重配 UTF-8（``errors='replace'`` 兜底；UTF-8 无不可编码字符，
   replace 实际不触发）；
2. ``os.environ.setdefault('PYTHONIOENCODING', 'utf-8')`` ⇒ 经 subprocess 继承的
   **子进程 Python 同规**。必须走 env 传播：实测 registry 环境变量/用户 profile
   都**不穿透**进程树（子进程沿用父 env 块），只有父进程 env 注入有效。

边界（刻意不做）：不改 ``open()`` 默认编码、不动 locale、不动机器配置
（2026-11-03 用户裁定「仅仓内修复」）；Linux（默认 UTF-8）零影响。
"""
import os
import sys

__all__ = ['force_utf8_stdio']

_DONE = False


def force_utf8_stdio():
    """重配本进程 stdio 为 UTF-8，并向子进程传播同规约定；幂等。"""
    global _DONE
    if _DONE:
        return
    _DONE = True
    os.environ.setdefault('PYTHONIOENCODING', 'utf-8')
    for _s in (sys.stdout, sys.stderr):
        try:
            _s.reconfigure(encoding='utf-8', errors='replace')
        except Exception:
            pass
