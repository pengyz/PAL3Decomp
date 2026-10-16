---
name: gotcha-annotation-type-churn-empty-extern-render
description: 并发编辑窗内注解类型瞬缺 ⇒ 就地 extern 机制渲染出「空型名」坏行（globals.h 全灭）⇒ S2 瞬间塌到 0/205 的总体幻影；判据=全单元同崩一行 globals.h + stage 源静态（崩/好双态同源可复现）
type: gotcha
created: 2026-10-16
updated: 2026-10-16
status: active
sources: [session-2026-10-16]
---

**现象**：2026-10-16 22:14 一轮干净 `codegen all → probe → match`（排他闸 ps=0 放行）读数
**S2 0/205**（全灭），match 总体 **0/0**。逐单元错误完全同形：

```
pal3/src/globals.h:868  C2143  syntax error : missing ';' before '*'
pal3/src/globals.h:868  C2501  'g_pComposeUI' : missing storage-class or type specifiers
pal3/src/Combat/CCBAI.cpp:2559  C2065  'flt_17A8E68' : undeclared identifier   ← 就地 extern 浮点全局连锁
```

第一眼极易误判为「codegen stage 代码写坏了头文件」（当时 `pipeline/gen/stages/emit_headers.py`
等 10 个管线文件 dirty）——**实际不是**。

**机理（为什么）**：`globals.h` 的全局声明有两条来源（CLAUDE.md 设计原则：
"全局变量不依赖 export _globals…codegen 的**就地 extern 机制**是 fallback"）。
当某个全局的 **TYPE 名在注解数据里瞬态缺失**（并发编辑窗内被摘/被改名的毫秒级中间态），
就地 extern 的渲染拿到空型名，输出形如：

```cpp
extern  * g_pComposeUI;        // 型名空洞 ⇒ C2143 missing ';' before '*' + C2501
```

而不是合法的 `extern ComposeUI * g_pComposeUI;`。一行坏声明被 `globals.h` 全局 include
⇒ **每个编译单元在同一家行崩** ⇒ S2 总体塌 0（总体幻影，非编译能力回退）。

**判据（如何识别，四条并置才可定性）**：
1. **全单元同崩一行**：错误堆指向同一 `globals.h` 行、同一标识符，C2143+C2501 成对
   （单元级问题是散点，头级问题是一行齐发）；
2. **崩标识符是就地 extern 型**：对照 `pal3/src/globals.cpp`/`globals.h` 有该全局、型名空洞；
3. **注解面在编辑窗**：`git status data/annotations/` 有 dirty + `find data/annotations -newermt '<短窗>'`
   有新改（并发批活跃证据）；
4. **崩/好双态同源**：stage 源 mtime 静态（早于崩点）的前提下，稍后单独
   `python pipeline/cli.py codegen headers` 复渲染出**合法行**
   （实录：`extern ComposeUI * g_pComposeUI; // 0xdc0de8`，2990 globals）⇒ 排除 stage 代码损坏
   （stage 坏则同源可复现崩行）。

**⚠️ 反面教训（本次实录）**：首判「emit_headers.py 半成品坏头」**错**——stage 源 20:47 起静态，
22:14 崩点 40 分钟后同一 stage 源渲出好行 ⇒ 真凶是**注解类型瞬态 churn**。
同源双态对比是分水岭判据，没有它就会把并发编辑的瞬态数据洞栽赃给 stage 代码。

**修法（三层）**：
1. **即时**：等注解编辑窗闭合（或补回缺失型名）→ `codegen headers` 抽验该行 → `probe` 复测
   ⇒ S2 恢复（本次 22:5x 复验 headers 行已合法）；
2. **加固（挂账，R15（data/status/_d1_ledger.md）先行单测）**：就地 extern 渲染遇**空型名**应
   **fail-loud**（出 `_todo_type_xxx` + 门禁报错），禁止输出语法坏行——坏行让 205 个单元
   全部替一个数据洞陪葬，信噪比灾难；
3. **诊断捷径**：`sed -n '<行>p' pal3/src/globals.h` 看崩行是否缺型 + `git status data/annotations/`
   看编辑窗，两条对上即本坑，勿跑全链定位。

**数字引用**（全部当场读，2026-10-16）：S2 0/205 @22:14:56 · 崩点 globals.h:868 ·
stage 源静态 20:47（emit_headers.py）/16:47（stage5_fixup.py）· 复验好态 2990 globals ·
全单元 C2143+C2501 同形 + C2065 `flt_17A8E68` 连锁。
