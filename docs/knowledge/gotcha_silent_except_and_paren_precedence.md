# 静默 except + 括号优先级：`list(x or {}).items()` 的经典双坑

事实：stage2 hook 里 `for k,v in list(getattr(store,'method_sigs',None) or {}).items():`
在生产**静默不生效**——Python 先求值 `list(...)` 得 list，再对 list 调 `.items()` ⇒
AttributeError，被外层 `except Exception: pass` 吞掉。独立测试一切正常（测试直接调纯函数），
只有 in-process 复现才现形。

**为什么：** ①括号优先级：`list(A or B).items()` ≠ `list((A or B).items())`——前者把 dict
变成 list 再找 .items()。②`except Exception: pass` 把接线错误变成"功能不触发"，无任何信号。
③单测测的是纯函数，接线层（map 构建/取数）不在覆盖内 ⇒ "测试绿但生产不触发"。

**何时使用：** 写 store 取数+变换接线时——(a) 括号显式：`list((x or {}).items())`；
(b) 接线的 except 至少 `except Exception as e: print('[hook-skip]', e)`（可观测）；
(c) 接线层加一条 **in-process 集成测**（真 store + 真 run()），不只纯函数测；
(d) 诊断"生产不触发"三步法：独立形调纯函数 → in-process 调 run() → 逐段复刻取数段。
