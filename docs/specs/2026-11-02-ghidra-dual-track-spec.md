# Ghidra 双轨验证 Spec（2026-11-02）

> 状态：立项 · 分支 `feature/ghidra-dual-track` · 来源：redivivus 方法考古 + 变向裁定

## 1. 背景与问题

PAL3 匹配反编译当前的编译错误面（S2 128/215，~1199 错）**混杂两类问题**：
- **annotation 层错误**（类型/归属/命名缺口）——可修、应修
- **Hex-Rays 反编译器硬约束**（方言/优化码失真/类型传播极限）——codegen 层不可解

二者在单轨（IDA/Hex-Rays/codegen）内难以分离，导致修复归因成本高、
「已知限制」登记册（hexrays_limit 15 文件）可信度存疑。
redivivus（D2 1.14d 重建，`/home/peng/workspace/redivivus`）证明了另一条路：
Ghidra 直出合法 C + 薄壳发射 + 编译验证，其工作流核心
（`ghidra-reconstruct` + `ghidra-mcp`，已克隆至 `/home/peng/workspace/`）
**binary-agnostic**，可直接服务 PAL3.exe。

## 2. 目标与非目标

### 目标
- **G1（核心）分离显微镜**：建 Ghidra 验证轨，编译错误差分产生
  「注解真错 / Hex-Rays 约束」自动定量清单
- **G2 纯注解问题基线**：验证轨编译错误=纯 annotation 问题 ⇒ annotation 战役
  快速定位（不被 Hex-Rays 约束拖累）
- **G3 约束边界登记册**：hexrays_limit 15 件过三路（转注解/转手写/真硬接受）重审
- **G4 顺带评估**：cpp-parser/37-pass 基建在验证轨实操（为后续「2a 结构借壳/
  2b 本体借用」决策攒数据）

### 非目标
- **不产交付源码**：验证轨输出永不进字节匹配轨（L1/字节轨恒 IDA/MSVC6）
- 不追求验证轨可读性（quick 预设=仅伪影清除=「可编译」铁律档）
- 不迁移字节轨工具链（迁移 ROI 负裁决已录：grep 续账 A-D）

## 3. 架构

```
annotation JSON（单一真相源，不动）
   │
   ├─[既有] apply→IDB→Hex-Rays→codegen ──→ C₁（混合错误面）──→ 语料 A
   │
   └─[新·转换层] annotation_import（本仓新件，TDD）
        → Ghidra 库（派生物，可弃，headless 重建）
        → ghidra-mcp（导函数/类型/全局）
        → ghidra-reconstruct [quick 预设] → 丑 C（薄壳 TU）
        ──→ mingw 编译 ──→ 语料 B（纯注解错误面）

差分（B−A）= Hex-Rays 约束清单 ✦G1 核心产出
差分（A−B）= Ghidra/转换层噪声基线
交集 = 注解真错双证 ✦G2
```

## 4. 组件与来源

| 组件 | 来源 | 状态 |
|---|---|---|
| ghidra-reconstruct | github.com/jaenster/ghidra-reconstruct | ✅ 已克隆（TypeScript，~37 AST pass 插件化，quick/full 预设）|
| ghidra-mcp | github.com/jaenster/ghidra-mcp | ✅ 已可克隆（daemon/local-worker 双模）|
| Ghidra 11.2.1 | tools/ghidra/ghidra_11.2.1_PUBLIC（本仓既有）| ✅ headless 可用 |
| **annotation_import 转换层** | **本仓新件**（tests/ TDD，mangled 真值锚）| ⬜ 待实现 |
| project.json 配置 | 本仓新件（modules/typeOwnership 映射 PAL3 类/头）| ⬜ |
| 差分器 | 本仓新件（编译错误集对账）| ⬜ |

### 转换层语义要求（关键）
- 注解 JSON → Ghidra：structs known_members（偏移+型）→ Ghidra Structure；
  functions/methods 签名 → Function 签名（调用约定/this）；globals → 数据符号
- **载体形诚实化**：`void __fastcall(int self)` 等 IDA 载体约定 → thiscall 本体
  （不让 IDA hack 污染验证轨信号）
- 已 mangled 名直通（禁重绞——复核 D1 教训）；零参全局 `XZ` 形
- `_todo_`/`sub_` 占位名=过（可读性非目标）

## 5. 铁律与约束

1. **VERIFICATION-ONLY**：验证轨产出零交付义务、可整体弃件（Ghidra 库=派生物）
2. **不准确=不判定**：差分归因只报「有差异」，成因判读须证据；两轨同错≠注解错定论
   （需抽样双证）
3. **不动字节轨**：本分支零 annotation/字节轨行为变更（若确需注解修正，回 master
   走完整管线纪律）
4. **quick 预设=可编译铁律**：验证轨禁用美化 pass（goto/cleanup/简化=全关）
5. 失败即弃：试点切片若分离价值不兑现（两轨错误高度重合）⇒ 降级为
   「Ghidra 单函数对偶旁证」用法，不扩全量

## 6. 里程碑

| 里程碑 | 内容 | 验收 | 估 |
|---|---|---|---|
| **M1 切片试点** | 转换层 v0（一类族+globals，~20 函数）+ project.json + quick 出丑 C + mingw 编译 | 差分表产出（B−A/A−B/交集三桶+样例归因）| 1-2 天 |
| M2 全量验证轨 | 转换层扩全量注解；Ghidra 库全函数 decompile；差分全量表 | hexrays_limit 15 件初判（转注解/手写/真硬）| 2-3 天 |
| M3 边界登记册 | G3 三路重审 + 差分清单归档 spec | `docs/specs/hexrays-constraint-boundary.md` 落 | 1 天 |
| M4（条件门） | 2a 结构借壳（现有 Python 变换插件化+tiering）——**仅当** M1 数据支持 | L1 零漂移实证（发射逐字节不变）| 2 天 |

## 7. 风险与止损

| 险 | 缓解 |
|---|---|
| 转换层自身 bug 污染差分信号 | TDD+mangled 真值锚（IDA 实验真值对）；M1 前转换层测试≥覆盖率硬门槛 |
| ghidra-mcp/ghidra-reconstruct 运行依赖（Node/pnpm/daemon）| 本地 worker 模式（stdio，免 daemon）；依赖装机步骤入 docs |
| Ghidra 自身 quirk 混入 | A−B 桶=噪声基线持续记账；不据单例下结论 |
| 验证轨拖累主线 | 时间盒：M1 超 3 天即停，转旁证用法 |

## 8. 验收判据（M1 完成定义）

1. 切片函数集双轨编译错误清单落档（`data/status/dual_track_m1_diff.json`）
2. 每条差异可溯源（错误码/单元/行级锚点）
3. 「仅 A 有」簇 ≥1 条可归因为 Hex-Rays 约束（分离价值实证）——否则走失败即弃
4. 全程零字节轨变更（git diff 空对 pal3/src 与 data/annotations）
