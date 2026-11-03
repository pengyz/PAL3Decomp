# 对拍实验设计（UT obj 一致性 + 字节一致路线）

> 2026-11-03 · 通用反编译工作流（pal3-redivivus）× PAL3Decomp 双仓
> 目的：①验证 annotation→redivivus **数据导入正确**（obj 级对拍）②梳理工作流、规划字节一致路线

---

## 实验一：UT obj 对拍（数据导入正确性裁判）

### 原理
同一批 annotation 数据分别走两条渲染轨，**同编译器（VC6）**编译同名 UT：
- **A 面（annotation 轨）**：`data/annotations` → apply_annotations → IDB → Hex-Rays → codegen → `pal3/src/<UT>.cpp` → VC6 → `obj_A/<UT>.obj`（既有管线产物）
- **B 面（redivivus 轨）**：同 `data/annotations` → 转换层(changeset) → Ghidra 库 → reconstruct[quick/full] → `output/<UT>.cpp` → VC6 → `obj_B/<UT>.obj`

**对拍判据**（对拍一致性=数据导入正确）：
| 层 | 判据 | 意义 |
|---|---|---|
| L0 编译 | B 面 UT 能过 VC6 编译（部分 UT 即开张）| 出码可用性 |
| L1 obj 对拍 | 同名 UT 的 obj 逐函数比对（L1 三限定口径：截断/等长/reloc 4B don't-care）| **一致函数=两轨对同一数据的渲染收敛=导入正确** |
| 差异三桶 | `A_only 形`/`B_only 形`/`共有但不同` → 归因：导入错误 / Hex-Rays 约束 / Ghidra 伪影 | 导入错误桶=转换层 bug（**本实验的靶**）；余两桶=对拍语料 |

### 为什么 obj 对拍能验「导入正确」
两条轨的**代码形**不同（反编译器差异），但**数据层**（struct 布局/成员偏移/签名/全局址）同源。
- 导入正确 ⇒ 两轨渲染的**成员访问/常量/布局钉一致** ⇒ 可比函数 obj 高一致率
- 导入错误（偏移错/型错/名错）⇒ **结构化差异模式**（成员访问偏移漂移/宽度变化）⇒ 差异桶里可机器归因
- 保底基线：**数据段对拍**（全局初值/vtable 槽/字符串）——纯数据 UT 应**逐字节一致**（最强导入正确性证明，零反编译噪声）

### 机制
```
① 数据导入：annotation → gen_plan → changeset emitter → ghidra-mcp 灌注（未做=当前空数据态）
② B 面出码：reconstruct [--transform-preset quick|full] → pal3-redivivus/project/output/
③ B 面编译：gen_project_cmake --project pal3（toolchain=vc6）→ 编译过者收 obj_B
④ A 面 obj：PAL3Decomp 既有 build（probe_census 同源）→ obj_A
⑤ 对拍器：compare_pal3.py/gbengine_compare（L1 三限定）逐 UT 逐函数 → 三桶报告
⑥ 报告：data/status/dual_track_obj_diff.json（schema=diff_tool 同族，带 obj 级 trace）
```

### 验收
- ≥1 个 UT 双面可编译且完成 obj 对拍
- 数据段 UT（若有）逐字节一致
- 差异清单三桶归因（导入错误桶给出具体 op→修复闭环）

---

## 实验二：redivivus 工作流梳理 + 字节一致路线

### 工作流现状（已跑通的全链）
```
项目配置(projects.json: exe/toolchain/ghidra) → Ghidra 库(自动分析/annotation 灌注)
  → ghidra-mcp daemon 会话（normKey patch）→ ghidra-reconstruct extract(函数/类型/全局)
  → 37 AST pass[quick|full] → output/ 丑C 树 → [VC6 编译门] → [obj/字节比对]
空数据基线：Functions 5946 · Types 382 · Globals 8371 · 24 files · Warnings 2470
```

### 字节一致路线（三级演进）
| 级 | 判据 | 编译器 | 现状 |
|---|---|---|---|
| **L1 编译级** | UT 过编译+静态断言（sizeof/offset 布局网）| mingw 快检 / VC6 终判 | 部分开张（实验一①）|
| **L2 obj 一致级** | 同名 UT obj 对拍（三限定）· 数据段逐字节 | **VC6**（唯一字节真值） | 实验一主体 |
| **L3 字节匹配级** | 重建产物 vs **PAL3.exe 原函数**逐字节（=PAL3Decomp 的 L1 三限定口径）| VC6 /O2 /Ob2…（原 flags） | 终态目标 |

### 字节一致的达成要素（从 redivivus 经验继承）
1. **原编译器+原 flags**：`toolchains.json` vc6 族已钉（/O2 /Ob2 /Oi /Ot /Oy /Gy /G5）——D2 的 BYTE-MATCHING.md/asm_matching 即此裁判
2. **COMDAT/对齐/尾填充**：Ghidra 出码的布局钉（成员偏移/尾 padding）须与原编译器布局规则一致——静态断言网先行（继承 D2 的 static_assert sizeof 网形态）
3. **变换完备度**：37 pass 消伪影后残差=手写 overrides（ghidra-reconstruct/overrides 机制）——少数无 C 拼写函数的手写区
4. **逐函数棘轮**：字节匹配从数据段/叶子函数起（噪声最小），逐函数爬（asm_matching harness=比对器现成）
5. **对拍语料驱动**：实验一三桶（导入/Hex-Rays 约束/Ghidra 伪影）中后两桶=字节一致的修复路线图输入

### 与 PAL3Decomp 字节轨的关系（分工）
- 字节轨（IDA→codegen→MSVC6）：**主生产**（已有 L1 棘轮 184+）
- 工作流轨（Ghidra→reconstruct）：**数据验证+约束隔离**（实验一）→ 逐步承担字节一致能力（L2→L3）
- 汇合点：数据层（annotation）双验后回输；字节匹配判据统一（compare_pal3 三限定）
