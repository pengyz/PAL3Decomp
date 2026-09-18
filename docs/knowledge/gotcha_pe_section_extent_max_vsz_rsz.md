---
name: gotcha-pe-section-extent-max-vsz-rsz
description: 读 PE 节必须用 max(VirtualSize, SizeOfRawData) 界定范围，否则 .rdata 尾部会被误判为未映射，产出"注解 vtable 指向未映射地址"这类假发现
type: gotcha
created: 2026-09-17
updated: 2026-09-17
status: active
sources: [session-2026-09-17]
---

**现象**：写取证工具读 `original/PAL3.exe` 的节内容时，若按 `VirtualSize` 界定节范围，
`.rdata` 上界算成 `0x56F178`（`0x56A000 + 0x15178`）。于是 `0x5704A8`、`0x57058C`、`0x5706EC`
等一批地址被判为"不在任何节内"，进而得出**假发现**：
"18 个注解 `vtables.addr` 指向未映射地址，是伪造的/陈旧的"。

**真相**：该 PE 的 `.rdata` 是 `VirtualSize=0x15178` 但 `SizeOfRawData=0x16000`。
加载器把 raw 数据一并映射 ⇒ **有效虚拟范围到 `0x580000`**，上述地址全部合法。
反证很直接：`objdump` 能看到 `0x5160cc: movl $0x5704a8,(%esi)` —— **ctor 真的安装了这张表**。
（`0x56a000 + 0x16000 = 0x580000`，正好与下一个节 `.data` 的 `0x580000` 相接。）

**为什么**：PE 节的虚拟占位由 `VirtualSize` 与 `SizeOfRawData` 中**较大者**决定，
按页对齐映射。只读 `VirtualSize` 的代码在"raw 比 virtual 大"的节上会**截断尾部**。
`0x56A000..0x56F178` 与 `0x56F178..0x580000` 之间并不是空洞，而是 `.rdata` 被截掉的那一段。

**何时使用**：
- 任何**绕过 IDA 直接解析 PE** 的取证脚本（读 vtable、读字符串、读 RTTI、按节过滤地址）。
  正确写法：`if sec_va <= va < sec_va + max(vsz, rsz)`。
- 看到"某地址不在任何节内/未映射"这类结论时，**先怀疑自己的节范围算法**，
  再用 `objdump -d --start-address=<该地址>` 或"是否有 ctor 安装它"做反证。
- 反面教训与本项目既有纪律同源：**自造解码器/自造映射会制造假象**（见 `vtable_scanner.py` 的
  "自造解码器会制造假象"）。本次差点据此去"清理虚假注解"，实际是要清理的是工具。