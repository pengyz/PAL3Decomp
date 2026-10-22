# asm-first 辩护

> 对抗性复核·仅论证，不改产品文件。现状：Path A = S2 56% · L1 17.2% · 360s/次。

## 论点 1: Hex-Rays 伪代码有损，补不回 MSVC 6.0 codegen（证据）
伪代码丢弃的恰是 /O2 /Ob2 /Oi /Ot /Oy 下决定字节的要素：指令调度、寄存器分配、jump table 形态、栈槽复用、/Gy COMDAT 排布。项目自证 `hexrays_limit = 62 文件 / 42.5%，"不修，记录为已知限制"`（CLAUDE.md 修复优先级）；Hex-Rays 不支持引用/模板，需 template_bases.json 打桥；"优化反编译产物：看起来对但字节不对"（核心困难 4）。annotation 再精确也是喂给有损编码器 ⇒ L1 17.2% 即此损耗的量化。

## 论点 2: asm-first 立即字节一致（证据）
asm = bytes：汇编回 .obj 后函数体即原字节，比对构造性成立。对照 Path A 的度量自带三限定：截断比较、长度相等、重定位 4 字节 = don't care，实测隐藏差异占 L1 字节 19.24%（docs/knowledge/gotcha_l1_reloc_dontcare_three_qualifications.md）；C1003 截断单元使总错误可完全不变。asm 比对逐字节、无 don't-care、无截断盲区。

## 论点 3: asm-first 增量可拆分（证据）
函数级独立编译/比对/替换/回退，验证成本 O(函数)；Path A 全局耦合——一处 annotation 改动须 apply→export→codegen→probe 全量重跑 360s。asm-first 下单次衰退的最大爆炸半径 = 一个函数，回退同粒度。

## 论点 4: Path A 修改易大衰退（证据）
R51 实证：59 条弱型改型 ⇒ S2 117→111 · 总错误 1268→1885 **+617**，已回退（data/status/class_review_progress.json:356；docs/knowledge/rule_pre_commit_evidence_checklist.md）。此后策略被迫"单点证据不足⇒冻结"。且棘轮回写基线 ⇒ 事后查文件无法判退化（CLAUDE.md 明文）。asm-first 把验证从指标代理换成字节本体。

## 承认的弱点
1. **不可维护**：终局交付物是可读 C++，asm 只是保字节地板的过渡态，长期是死胡同。
2. **混合编译复杂**：asm+C++ 的 COMDAT 折叠、vtable 布局、thiscall 约定、CRT 边界一个都不消失，且链接层是 S2 盲区（gotcha_s2_compiles_but_does_not_link.md）。
3. **数据段不在函数维度**：vtable/全局/字符串的字节一致仍需另案；"立即字节一致"仅覆盖 .text 函数体。
4. **双轨成本**：替换期 asm 与 C++ 并存，接口对齐是手工活。

## 结论
字节一致率与验证强度 asm-first 严格优于 Path A（永不回退的字节地板 + O(函数) 强验证），正对 L1 17.2% 平台期与 R51 型大衰退；但 asm 是手段非目的 ⇒ 推荐 asm-first 打底 → 函数级 C++ 重写收割（顺序而非互斥）。坚持纯 Path A 须先回答：42.5% hexrays_limit 谁修、19.24% reloc 隐藏差异谁验、R51 型全局大衰退如何避免。
