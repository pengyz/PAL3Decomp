---
name: gotcha-byte-match-metric-is-mangler-gated
description: matched/L1/partial 全部经过 mangler——mangled_map 生不出名字的符号直接计 unmatched，从不参与字节比对
type: gotcha
created: 2026-09-15
updated: 2026-09-15
status: active
sources: [session-2026-09-15]
---

**现象**：`pipeline/cli.py match` 报告的 `symbols=189` 里，长期有 `unmatched=60`（32%）**从未被字节比对过**。
它不是"比对失败"，而是"**没进比对**"。

**为什么**：
`pipeline/compare_pal3.py:match_symbols` 的匹配路径只有两条：

```python
for sym in funcs:
    if sym in mangled_map:            # ← 路径 1：mangler 生成的键（唯一对 C++ 符号有效的路径）
        matched[sym] = mangled_map[sym]; continue
    if sym.startswith('?'):
        continue                       # ← mangled 但 mangler 生不出 ⇒ 计入 unmatched，就此结束
    cand = re.sub(r'@\d+$', '', sym[1:] if sym.startswith('_') else sym)
    if cand in base_idx: matched[sym] = base_idx[cand]   # ← 路径 2：只对非 '?' 符号生效
```

`.obj` 里的 C++ 符号**全部以 `?` 开头** ⇒ **路径 2 贡献恒为 0**。
⇒ **`mangled_map`（即 `pipeline/ida/vc6_mangler.py`）是字节匹配判据的单点故障。**

实证（2026-09-15）：mangler 的 4 处名字编码缺陷修好后，
`matched` 129→150、**`L1` 6→14（+133%）**、`unmatched` 60→39——
即 **21 个此前无法评分的函数第一次进入比对，其中 8 个字节全同**。

**何时使用 / 操作规程**：
- 看 `match` 输出时，**必须同时看 `unmatched`**。`symbols` 里的 `unmatched` 占比高
  说明判据的**覆盖率**低，此时的 `L1`/`partial` 只代表"可判定子集"，不代表全貌。
- **报 `L1`/`partial` 时必须一并报分母**（`matched`）——分母一变，跨轮比较即无效
  （本项目已有"分母不同即不可比"的历史教训）。
- ⚠️ **"名字命中"不等于"参与比对"**（2026-09-15 补充）。
  `matched` 只表示 `mangled_map` 里**有这个名字**，而字节比对还需要该符号的
  **原始二进制地址 `va`**（`compare_units` 用 `e['va']` 定位 `.text` 偏移）。
  由名字供给合成的条目（见 `build_mangled_map` 的 `_from` 标记）**没有 `va`** ⇒
  名字对上了也**无法比对**。实测一次扩池中：`matched` 129→164（+35），
  但其中 **23 个无法比对** ⇒ **真正参与比对的只有 141（+12）**。
  ⇒ 判据必须**同时报三口径**：`matched` / **可比对（`matched − unresolved_synth`）** / `L1`。
  **单看 `matched` 会高估进展**——`L1` 因为定义上必然经过比对，是三者中唯一不会被此失真污染的。
- 改动 `vc6_mangler.py` 或 `match_symbols` 后，**先看 `unmatched` 是否下降**，
  再看 `L1`/`partial`；因为前者决定后者的定义域。
- **`unmatched` 的归因可完全离线做**（纯 Python 名字编码），不必占 IDB 窗口：
  见 `tools/mangler_bench.py`（复用已编译的 `.obj`）。