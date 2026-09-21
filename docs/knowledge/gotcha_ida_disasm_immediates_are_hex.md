---
name: gotcha-ida-disasm-immediates-are-hex
description: IDA 反汇编文本里的立即数是十六进制字面量（push 424h），用 %s 原样打印就会把 0x424 读成 424——差 4 倍，且会据此写出错误结论
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：IDA 的立即数是**十六进制字面量**，原样打印会看错 4 倍

## 现象

我写的 IDB 取证脚本用 `%s` 打印 `generate_disasm_line()` 里正则抓到的立即数：

```python
RE_PUSH = re.compile(r'\bpush\s+(?:offset\s+)?([0-9A-Fa-f]+)h?\b')
...
f.write("  push N = %-8s ..." % N)          # ✗ N 是 '424'，而源码里是 `push 424h`
```

输出 `push N = 424`，我据此写下结论"**IDB 推翻申报值 1060，真值 ≈424**" ✗——
而 `original/PAL3.exe.asm:267375` 实际是 **`push 424h`** ⇒ **0x424 = 1060** ✓，
**申报值是对的，我的"推翻"是误读** ✗，并已写进三处台账 ✗。

## 坑

1. **十进制/十六进制在这个仓库的关键数字上常常恰好差 ~4 倍而"看起来都合理"** ✓
   （424 vs 1060 都像"一个小对象"）⇒ 不会被常识拦住 ✗。
2. 我的正则 `h?` 让 `424h` 与 `424` 都能匹配 ⇒ **丢掉了进制信息** ✗。
3. 这个错误**流进了台账并被当成事实引用** ✗ ⇒ 由**独立复核者**读 asm 才发现 ✓。

## 规则

- 从 IDA 文本抓立即数后**一律 `int(x, 16)` 转换**，并在输出里**同时打印两种形态**：
  `push N = 424h (0x424) = 1060 十进制` ✓。
- **写结论前必须回原始 asm 核对该行**（`grep -n "push 424h" original/PAL3.exe.asm` ✓）。
- 与 [[page:gotcha-annotation-authored-names-are-claims-not-evidence]] 配合：**进制、归属、尺寸三层都要各有一个不自证锚** ✓。
