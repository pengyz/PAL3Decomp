---
name: gotcha-asm-funclets-without-proc-need-host-attribution
description: MSVC/IDA 的 asm 里，SEH unwind funclet（`; START OF FUNCTION CHUNK FOR X`）没有自己的 `proc near` ⇒ 按"proc 边界"归属会把其中所有站点挂到文件里最后一个 proc 名（实测 213/466 全错）；且 END 之后宿主未知时应失效安全（宁可缺失也不误挂）
type: gotcha
created: 2026-09-20
updated: 2026-09-20
status: active
sources: [session-2026-09-20]
---

# gotcha：asm 的 funclet 没有 `proc near`，必须按 chunk 头归属宿主

## 现象

MSVC 生成的 SEH 展开代码以独立 chunk 出现：
```
; START OF FUNCTION CHUNK FOR sub_403370
   ...
; END OF FUNCTION CHUNK FOR sub_403370
```
它**没有自己的 `proc near`** ✗。若解析器只用 `proc near` / `endp` 划边界，这些行会**沿用上一个 proc 名** ✓
—— 而"上一个 proc"往往是**文件里最后出现过的**那个 ✓ ⇒ 实测 **213/466（45.7%）** 站点全被挂到同一个名字
`sub_55D67E` ✗（该名字与这些站点毫无关系 ✓）。

## 规则

1. **边界识别必须包含 chunk 头**：`^;\s*START OF FUNCTION CHUNK FOR\s+(\S+)` ⇒ 宿主取该名字 ✓
   ⚠️ **必须在剥离行尾注释之前匹配** ✗ —— chunk 头**本身就是注释行**（以 `;` 起头 ✓），
   若先做 `line = raw_line.split(';',1)[0]` 再匹配，得到空串 ⇒ **永不命中** ✓（本项目踩过这个坑 ✓）
2. **失效安全优于猜** ✓：`; END OF FUNCTION CHUNK FOR X` 之后若出现站点而**没有新边界**，
   宿主应记为**未知（`None`）** 而不是继续沿用 X ✓ —— 宁缺失也不误挂 ✓
   （对当前 asm 该间隙站点数 = 0 ⇒ 是 no-op ✓，但 asm 可被替换，不能依赖"当前为 0" ✓）
3. **此类"归属器"的验收必须用集合等式** ✓：站点行集合 == asm 中相关 call 行集合（无漏无重 ✓），
   并抽样核对**名字**（如 514955→`sub_403370`、515537→`sub_41F6F0` ✓），而不只看条数 ✓
4. 同族陷阱：任何"按局部标记推全局实体"的解析（按 `proc`、按 `section`、按 label ✓）
   都要问一句"**没有该标记的合法情形**是什么" ✓
