# 立场 B：asm-first 辩护书（对抗性复核·仅论证，不改产品文件）

> 主张：提取 asm → 修正可编译 → 立即字节一致 → 按函数 C++ 重写逐步替换，每次替换 = 重编译 + 字节比对。
> 现状对照：Path A = S2 56% · L1 17.2% · 360s/次 · R51 +617 大衰退 · 知识库 109（gotcha 77 = 教训驱动）。

## 核心论点与证据

**① Path A 的天花板是 Hex-Rays 固有的——伪代码有损，永远补不回 MSVC 6.0 codegen 信息。**
证据（项目自身数据）：`error_classifier` 分类中 `hexrays_limit = 62 文件 / 42.5%`，处置是"不修，记录为已知限制"——**近半失败被项目自己宣判为 Hex-Rays 能力上限**。CLAUDE.md 承认"优化反编译产物：看起来对但字节不对"；Hex-Rays 不支持引用/模板，codegen 需 `template_bases.json` 打桥。伪代码丢弃的恰是 /O2 /Ob2 /Oi /Ot /Oy 下决定字节的东西：指令调度、寄存器分配、jump table 形态、栈槽复用、`/Gy` COMDAT 排布。annotation 再精确也只是喂给一个**有损编码器**；L1 17.2%、partial 匹配率 6-12%（`G0_BASELINE.md`）就是这个损耗的量化。

**② asm-first 立即字节一致：asm = bytes，验证是构造性成立的。**
反汇编文本经 masm（`tools/` 内已有 MSVC 6.0 工具链）汇编回 .obj，函数体字节即原字节，cmp 平凡通过。对照：Path A 连"字节一致"的度量都在做让步——L1 判据三限定（截断比较、长度相等、**重定位 4 字节 = don't care**），实测隐藏差异占 L1 字节 19.24%（`gotcha_l1_reloc_dontcare_three_qualifications.md`）；C1003 截断单元让总错误数完全不变。asm-first 的比对逐字节、无 don't-care、无截断盲区。

**③ asm-first 增量可拆分（函数级），验证成本 O(函数) 而非 O(全管线)。**
每函数一个 asm 单元，独立编译、独立比对、独立替换、独立回退。Path A 是全局耦合管线：一处 annotation 改动 → apply→export→codegen→probe 全量重跑 360s，且"修改易大衰退"（R51 +617，`data/status/class_review_progress.json:356`）。asm-first 下一次衰退的最大爆炸半径 = 一个函数。

**④ 外部实践：matching-decomp 社区的标准路径就是 asm 打底。**
SM64 / OoT 等 N64 匹配反编译项目均以 `.s` drop-in 起步，逐函数换 C，裁判是 asm-differ 逐字节 diff；m2c 产出只作候选、不作裁判。同构结论：**反编译器输出是假设，汇编是事实**。

**⑤ Path A 的"强进步"指标实为弱验证。**
棘轮回写基线 ⇒ 事后查基线文件无法判断退化（CLAUDE.md 明文）；match EXIT=1 可能是编译崩塌的下游假象。知识库 109 中 77 条是 gotcha——管线 70% 的知识是"踩坑记录"，说明其不确定性由人肉教训兜底。asm-first 把验证从"指标代理"换成"字节本体"。

## 对 Path A 的反驳

- **天花板在编码器不在标注**：Phase 2 的手工 fix 本质是人肉把 Hex-Rays 丢掉的 asm 信息补回来——为什么不从 asm 直接出发？
- **360s×高频迭代 + 大衰退风险**让每步改进的期望收益为负（R51 +617 实证）。
- **42.5% hexrays_limit 永不修复** ⇒ Path A 的理论上限被钉在 ~58% 文件可收敛，L1 17.2% 距此尚远且逼近平台期。

## 承认的弱点（诚实）

1. **asm 不可维护**：终局交付物是可读 C++，asm 只是保字节地板的过渡态，长期是死胡同。
2. **混合编译复杂**：MSVC 6.0 asm+C++ 混合链接的 COMDAT 折叠、vtable 布局、thiscall 约定、CRT 边界问题**一个都不消失**，且链接层本就是 S2 盲区（`gotcha_s2_compiles_but_does_not_link.md`）。
3. **数据段不在函数维度**：vtable/全局/字符串/模板实例化的字节一致仍需单独方案。
4. **双轨成本**：替换期内 asm 版与 C++ 版并存，接口对齐是手工活；"立即字节一致"仅覆盖 .text 函数体，不含重定位站点与导入表。

## 结论

**字节一致率与验证强度：asm-first 严格优于 Path A**；asm-first 提供"永不回退的字节地板" + O(函数) 强验证，正对 L1 17.2% 平台期与 R51 型大衰退。但 asm 是手段非目的——建议 **asm-first 打底（保字节一致）→ 函数级 C++ 重写收割（保可维护）**，两条路径不是互斥而是顺序；坚持纯 Path A，则需先回答：42.5% 的 hexrays_limit 谁来修，19.24% 的 reloc 隐藏差异谁来验。
