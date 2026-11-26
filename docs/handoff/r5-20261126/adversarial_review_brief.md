# 独立对抗复核任务书（#9 SaleUI 池证据落位）

被审对象：`data/annotations/structs/SaleUI.json`（commit `7f9d6a636`），类 `SaleUI`，`binary_size=105912`(0x19DB8)。

## 复核纪律

- **只读**：不改仓库文件、不 `git commit`、不写 `data/annotations/`。
- **不复用作者的探针逻辑**：作者用的是 idalib 逐指令跟踪 `this`（disps/subobjs/calls）。请自选另一条路径（例如 objdump 反汇编 + 手工解 `??_L`/`??_M` 压栈、或 Hex-Rays 语料 ↔ 注解逐条对账、或直接读 `asm/pal3/ida_structs.json` 与 ctor 区间互证）。
- **不要运行 `python3 pipeline/cli.py`**：单管线通道，别人可能正在跑 loop。
- 不要 open/修改 `original/PAL3.exe.i64`（IDA 数据库，另有归属）。`original/PAL3.exe` 只读反汇编可以。

## 作者的声明（需独立验证，不要直接采信）

1. 真实布局来自 `??0SaleUI`(0x45A7B0–0x45ADC3) 与 `??1SaleUI`(0x45AE60–0x45B200)；含 5 个 `??_L`（eh vector constructor iterator）池：
   | 池 | offset | stride | count |
   |---|---|---|---|
   | UIFrameContainer[5] | 0x6394 | 152 | 5 |
   | UIFrameContainer[240] | 0x66F4 | 152 | 240 |
   | 未名 52B 元素池[240] | 0x11558 | 52 | 240 |
   | CCBResultWindow[30] | 0x14618 | 180 | 30 |
   | UIFrameContainer[30] | 0x15B30 | 152 | 30 |
   | UIFrameContainer[13] | 0x17A9C | 152 | 13 |
2. 其余成员按 ctor 写序 / ctor-dtor 相邻构造点间距落位，共 55 个成员。
3. 残留洞 3 段共 7,684B：`0xF574–0x10474`(3840)、`0x10564–0x10568`(4)、`0x10658–0x11558`(3840)，声称 ctor/dtor 无构造/清零证据。
4. `m_unk_0x150_view` / `m_unk_0x66f4_view` / `m_unk_0x11558_view` 三个名字是为兼容尚未刷新的 decomp 语料引用名；类型仍按池证据给。
5. 每个成员都有 `evidence_level` 与 `source`。

## 需要判定的 7 个问题（每条给命令 + 输出摘录 + 判定）

- **A. `??_L`/`??_M` 三元组核对**：反汇编 ctor/dtor 区间，逐个找出 push 的 `size/count/ptr`。cdecl 压栈序是 **先 dtor、再 ctor、再 count、再 size、再 ptr**（作者据此解读）。核对上表 6 个池。
- **B. 成员重叠/越界**：解析 `known_members`（键是 `"0x48"` 形十六进制字符串，值含 `span_bytes`），检查任意两成员区间不相交、且都不超过 0x19DB8。
- **C. span 自洽**：每个成员 `span_bytes` 是否等于「下一成员起始 − 本成员起始」；末成员是否刚好到类尾；3 个 `*_view` 成员长度与池元素尺寸是否整除。
- **D. 残留洞是否真无证据**：在 ctor/dtor 反汇编里找落在 `0xF574–0x11558` 的 `[esi+disp]` / `lea reg,[esi+disp]`；语料里也查一遍这些偏移的访问。
- **E. 命名合规**：是否全部是 `m_unk_<hex偏移>` 或既有语义名；有没有 `slot_N`、`sub_XXXX`、`_todo_`、数字后缀（如 `m_Data_1234`）。
- **F. 证据完备**：`evidence_level`/`source` 是否非空；A 级 source 是否真的写了可核对的 site 地址或三元组。
- **G. 找反例**：哪些成员的落位在 ctor/dtor 里找不到对应写/构造点（靠"相邻构造点间距"下界闭合的，强度更弱，要标出）；有没有把"清零（`rep stosd`/`memset`）"当成成员证据的过度推断。

## 交付

`docs/handoff/r5-20261126/adversarial_review.md`（若只读，把结论贴 thread 由 owner 落文件），结构：

1. 总结论：PASS / PASS-WITH-NOTES / FAIL
2. A–G 逐条：判定 + 关键证据
3. 反例/风险清单：严重度（BLOCKER/MAJOR/MINOR）+ 偏移/成员 + 建议处理
4. 实际用过的命令清单（便于复跑）

## 作者已做的自检（供对照，不可作为复核结论）

- `docs/handoff/r5-20261126/selfcheck.md` §6：语料↔注解交叉校验——55 个 `this->` 名字 54 个可解析（余 `UIWnd` 为基类），823 处越界索引（去重 6 处）全在 `m_unk_0x66f4_view`，落在残留洞内，判定非布局错误。
- `selfcheck.md` §7：上报 3 条既存缺陷（`UICaption` 尺寸 96 vs 自身证据 344、`?GetSys@NameSys` 实为 ctor、`InitColumnWidths` 的 `this[3]` 形态可疑）。
