---
name: debug-two-layer-localization-settrace-and-re-proxy
description: 定位"哪一行改写了我这行文本"的两个决定性手段——sys.settrace 行级追踪 + 代理 re 模块记录每次 sub 的入参/产出；本会话用它把 12 次猜测换成 1 次定位
type: debug
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# debug：定位"是哪一行代码改写了我这行文本"——行级追踪 + 代理 `re`

## 排查动作

codegen 的各 stage 是一长串 `re.sub` / AST 改写，一个调用点被改错时，
**读代码猜**是最贵的路径（本会话上一轮为此花了 12 次假设驱动修补，全部零效果）。
两个手段各 10 行，直接给出答案：

### ① 行级追踪（谁改的）

```python
import sys
target = stage3_cleanup.run.__code__          # 目标函数
prev = {}
def tracer(frame, event, arg):
    if frame.f_code is not target or event != 'line':
        return None
    c = frame.f_locals.get('code')
    if isinstance(c, str) and snap(c) != prev.get('s'):   # snap() 取关心的那一行
        print('line %-5d -> %s' % (frame.f_lineno, snap(c)))
        prev['s'] = snap(c)
    return tracer
sys.settrace(tracer)
out = stage3_cleanup.run(CODE, Ctx())
sys.settrace(None)
```

⇒ 打印出**变更发生的源码行号**（`stage3_cleanup.py:1242`）。

### ② 代理 `re` 模块（改成什么）

行号可能落在多行语句上，且 `re` 变量可能是拼接的 ⇒ 再用代理拿到**真正生效的 pattern**：

```python
import re as _re
class ReSpy:
    def __getattr__(self, k): return getattr(_re, k)
    def sub(self, pat, repl, string, *a, **kw):
        out = _re.sub(pat, repl, string, *a, **kw)
        if isinstance(string, str) and KEY in string and out != string:
            print('pattern : %r\nrepl    : %r\nbefore  : %s\nafter   : %s'
                  % (pat, repl, snap(string), snap(out)))
        return out
stage3_cleanup.re = ReSpy()      # 只替换该模块命名空间里的 re
```

⇒ 直接打印出 `pattern` + `repl` + before/after，**不再需要推断**。

### 先排除一层（省时间）

关掉某个可疑解析器看结果是否变化，能一步二分"病灶在哪一层"：

```python
s3._resolve_vftable_calls_ast = lambda code, ctx: code   # 禁用 AST 解析器
```

本会话即以此在 3 分钟内排除了整条 AST 路径（`_decode_vtbl_call` 的 SPY 始终无输出），
把范围收敛到 legacy 正则段。

## **为什么**

* `settrace` 的行事件能把"文本在哪个语句之后变了"钉死，但**行号归属多行语句时会有歧义**
  （CPython 把 `CALL` 记在语句起始行，`STORE` 记在末行）⇒ 需要 ② 补齐"到底是什么 pattern"。
* 代理 `re` 是**无侵入**的：不改被测代码，只在该模块的命名空间里换掉 `re`，
  因此拿到的是**真实运行路径**，不是"我以为的路径"。
* 与 R13（grep-verify 补丁是否落地）互补：R13 确认"我的改动进去了"，
  本条确认"是**谁的**改动改坏了这行"。

## **何时使用**

* 生成物某行内容与预期不符，且候选改写点多于 2 个（`grep -n` 出 3 处以上 `re.sub`）；
* 改动"看起来在该行/该函数"但产物无变化；
* 接手一条长 stage 链（`stage1..stage5`）而要快速建立"哪一层负责什么"的心智模型时。

配套纪律：定位完成后**把数字写进代码注释与知识条目**（本会话即把
`C2227 −41 / C2039 +22 / S2 ok 75→74 / L1 35→34` 写进 `stage3_cleanup.py` 该 `re.sub` 上方），
下一个会话就不必重新测量。