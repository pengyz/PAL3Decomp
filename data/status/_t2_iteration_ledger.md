# T2 迭代台账（2026-10-13 · pal3-converge · 迭代 2 收口）

**会话**：pal3-converge · **成员**：diagnoser（T16 收口，T6 等价）
**覆盖**：T8 诊断 → T9-T15 七任务实施（八任务含 T8）
**收口态基线**：S2 **112/209** · 总错误 **1434** · L1 **104** · matched **628/758** · partial 449 · L1 率 **104/553 = 18.8%**

---

## 一、本迭代裁决（Decisions）

### D1 · 判据 v2.1：L1 绝对数为主（`aeb0adf41`）
- **背景**：迭代 1 时判据是 L1 率（L1/(L1+partial)）；但解冻可测性会让分母（partial）快速膨胀，L1 率会被稀释甚至下降（如 18.7%→18.8% 只微增但 L1 从 86→104 = **+18**）
- **裁决**：**主判据改为 L1 绝对数**（`aeb0adf41` docs/knowledge）；L1 率作参考
- **理由**：L1 绝对数直接对应字节全同函数数，是最终目标；L1 率受可测性分母影响，不宜作主判据
- **Confidence: high**（本迭代 8 任务 L1 绝对数单调增长：86→94→103→104）

### D2 · 双轴方法论落地（T6 提出，本迭代采纳）
- **背景**：迭代 1 修 PAL3/ParabolaCalculator 布局后 L1 不动（P0 目标是可测性解冻）
- **裁决**：**P0 解冻 + P1/P2 字节修复交替进行**，双轴（L1 + S2 绿单元）同时追踪
- **落地**：T9 (P0.5 memfnptr) → T11 (P2 类型坍缩) → T12 (可变参) → T13 (M3 lvar 归并) → T14 (P2 类型坍缩三处) → T15 (P1 E.T 批) —— 混合推进
- **效果**：S2 101→112 (+11) · L1 86→104 (+18) · 总错误 1720→1434 (-286)

### D3 · T13 反证 T12 定性（诚实迭代范例 `42e8d0bec`）
- **背景**：T12 修可变参 sig 时首轮误判 `Combat::LogMessage` 为静态，产生 11 处 C2664
- **裁决**：**当场读抓误判 + 立即回退**（诚实迭代），修正判据为「无 __thiscall 且 首形参非 this 且（明写 __cdecl 或可变参）⇒ 静态」
- **教训**：`data.py` 的静态判定不能只看 `__cdecl` 明写；**可变参会丢调用约定标记**，必须看首形参是否 `Cls *this`
- **沉淀**：`docs/knowledge/gotcha_...`（诚实迭代范例）

### D4 · T14 保守保留原形的取舍（禁猜测）
- **背景**：T14 修 E.T 直读形时遇 3 处（CEffAudio/CEffCustomShape/CEffQuad）的 `CTaskTpl_` 子对象偏移**无 annotation bases 条目**，无法确定偏移
- **裁决**：**保守保留 `&E.T` 原形**（不猜测 +12），该 2-3 单元**由绿转红**，大声报错 > 静默错位
- **后续**：T15 补 annotation bases（A 级 lea 直证三处 `@12`）⇒ C2273 3→0 ✓
- **教训**：**宁可让单元红，不要猜偏移**（本仓铁律：禁猜测性修改）

### D5 · 搭桥不接线第 7 次（`ab056bf4f`）
- **背景**：T13 发现 `dedupe_identical_lvars` **早已 TDD 落地但从未接线**
- **裁决**：本次**接线**（stage3_cleanup 新增 `dedupe_lvar_decls`）
- **教训**：本仓已 7 次"搭桥不接线"——**改工具必须 grep 核实已接线**（R13）

---

## 二、本迭代教训（Lessons）

### L1 · 三段式验证（病灶层三问 + Evidence + Confidence）
- **病灶层三问**必答（哪一层 / 消费者读哪份声明 / 报错还缺什么）
- **Evidence** 必须 A 级二进制（objdump 指令 + 地址）或 MSVC6 编译器探针
- **Confidence** 必须显式标注（high/medium/low）
- **本迭代 8 任务全部遵守** ✓

### L2 · 诚实迭代（当场读抓误判 + 立即回退）
- T12 首轮误判 `Combat::LogMessage` 为静态 ⇒ 产生 11 处 C2664
- **当场读**（非事后查基线）抓到误判 ⇒ **立即回退** + 修正判据
- **不能事后查基线文件判断退化**（本仓铁律）

### L3 · 搭桥不接线第 7 次（R13 缺失的代价）
- `dedupe_identical_lvars` 早已 TDD 落地但**从未接线**（第 7 次同型）
- **教训**：改工具必须 `grep` 核实已接线（R13（`data/status/_d1_ledger.md`））

### L4 · scope 留余量（T10 inScope 裁决 `ebd5801cb`）
- T10 遇 `include/gbengine/gbRenderEffect.h` 访问级问题——**outOfScope**（annotation 层之外）
- **裁决**：留余量挂账，不越界改；下轮独立处理
- **教训**：任务 inScope 有明确边界时，越界改动会让复核混乱

### L5 · verify 自测（T14/T15 的 verify grep）
- T14/T15 改 codegen 后**自跑 verify grep**（如 `grep -c "C2273" ...`）确认目标错误已消除
- **教训**：改动后当场 verify（不依赖"应该没问题"）

---

## 三、挂账交接（下轮）

| 项 | 归属 | 备注 |
|---|---|---|
| **`CEffQuad` 1 错残留** | 前存 C2664 NewTexture 参数形 | 独立轮 |
| **T15 附带扫的 3 行** | E.T 丢 cast / E.T 赋值形 / lvar 型仲裁 | 禁猜测不改，独立轮 |
| **`Calc*/Insert/Init` 4 错** | M7/lvar 族 | P2 类型坍缩后续 |
| **`functions.json` owner 被忽略**（F5②）| annotation 层 | 只报未改行为契约 |
| **354 条双认领归属债**（D2 口径）| 归属裁定独立轮 | T4 278 vs T5 354 口径已统一 |
| **233 个归属冲突**（t7 附带发现）| 归属裁定独立轮 | functions.json vs structs |
| **`0x00485230` 名字待证** | 二进制证据收集 | slot2 家族名冲突 |
| **`test_five_sites` 裸 glob** | 存量技术债 | `export_full.py:733`，独立轮 |
| **`adjudicate_lvar_type` 接线批** | T12 挂账 | 型仲裁接线（同 dedupe 模式） |
| **`FileSysDestory` typo** | annotation 层 | Destroy 真名需二进制证据 |
| **`__PAIR16__` / `_TEB`** | include 层 | MSVC intrinsic / Windows SDK |
| **`SingletonThunk_*` 6 错** | annotation 层 | 跨 PAL3/PalScript/PalScriptMgr 3 单元 |
| **`UIPostUpdate` / `SceneRenderWithRotation` 归属错** | annotation 层 | 需 A 级证据证真身 |

---

## 四、迭代 2 效果对照（判据 v2.1 `aeb0adf41`）

| 指标 | 迭代 1 收口 | 迭代 2 收口 | Δ | 判据 |
|---|---|---|---|---|
| **L1 绝对数**（主）| 86 | **104** | **+18** ⭐ | ✅ **主判据增长** |
| **S2 绿单元** | 101/209 | **112/209** | **+11** | ✅ 结构改善 |
| **总错误** | 1720 | **1434** | **−286** | ✅ 大幅下降 |
| **PAL3.cpp 错误** | 94 | **50** | **−44** | ✅ |
| **C2273/C2274** | 162 | **0** | **−162** ✓ | ✅ P1 E.T 直读形清零 |
| **matched** | 520/613 | **628/758** | **+108/+145** | ✅ 可测性解冻 |
| **partial** | 373 | 449 | +76 | 可测性解冻 |
| **L1 率**（参考）| 86/459=18.7% | **104/553=18.8%** | +0.1pp | ⚠️ 分母失真，仅供参考 |

**L1 率说明**：
- 分母（L1+partial）从 459 膨胀到 553（+20%），L1 率仅 +0.1pp 但 **L1 绝对数 +18**（+21%）
- **主判据是 L1 绝对数**（判据 v2.1）：86→104 单调增长 ✓
- **离开 18-19.5% 平台**：需 ≥ 19.6%。当前 18.8%，分母持续膨胀下需 L1 增速 > partial 增速
- **P1 E.T 直读形清零**（162→0）是本迭代最大字节面胜利

**迭代 2 里程碑**（T14 突破 `963496bce`）：
- **L1 累计 +17**（86→103，T14 后）→ T15 后 **+18**（104）
- **S2 绿 +11**（101→112）
- **P1 E.T 直读形清零**（162→0）

---

## 五、验证证据（本 T16 收口）

| 项 | 命令 | 结果 |
|---|---|---|
| 全量 loop 端到端（含 export）| `python pipeline/cli.py loop --expect-s2 112/209 --expect-errors 1434 --expect-l1 104` | apply 0/9.9s · export 0/149.3s · codegen 1/180.4s（**已归因**：新失败 0 · 新错误 5 条含 C1003 un-truncation · 净错误 −286）· S2 **112/209** ✓ · match 手动补齐 |
| 三基线刷新 | `regression_detector.py --save-baseline` + `compile_regression.py --update-baseline` + match 自动 | `baselines/20261013_041606.json`（209 文件 112 ok 97 fail）· `compile_baseline.json` 已更新 · `s4_baseline.json` stats: symbols=758 matched=628 L1=104 partial=449 |
| L1 当场读 | `python pipeline/cli.py match` | `matched 628/758 · L1 104 · partial 449 · L1 rate 104/553 = 18.8%` · `[L1 ratchet] previous 104 -> current 104` ✓ |
| CLAUDE.md:150 参数 | 编辑 | `--expect-s2 112/209 --expect-errors 1434 --expect-l1 104`（从 `101/209 · 1720 · 86`）|
| 当场读数（非事后基线）| `probe_census.json generated_at=2026-10-13T04:14:42` | S2 112/209 · 总错误 1434 |

**Confidence: high**（多轮端到端 + A 级二进制证据 + 8 任务各自 verify grep；code_gen rc=1 已逐条归因 = 新失败 0 + C1003 un-truncation 同族暴露）

---

## 六、迭代 2 完成度总结

**T8→T15 八任务全部完成**：
- **T8 诊断**：PAL3.cpp 99 错按机制分 11 族 · CGameData.cpp 4 错分 4 机制 · 最高 ROI 簇 = memfnptr ABI 错配
- **T9**：memfnptr ABI 槽赋值修复 + `_Tidy` 访问面（S2 101→106 · L1 86→94）
- **T10**：判据 v2.1（docs）+ inScope 裁决（docs）
- **T11**：M1 访问级簇 + M10 签名簇（PAL3.cpp 94→81 · L1 →）
- **T12**：可变参 sig 丢调用约定根治（总错误 1630→1622）
- **T13**：M3 lvar 重复声明归并接线（PAL3.cpp 78→63 · 总错误 1622→1607）
- **T14**：P2 成员/全局类型坍缩三处（PAL3.cpp 63→56 · 总错误 1607→1600）
- **T15**：P1 E.T 直读形批（C2273/C2274 162→0 · L1 94→103）+ 补 bases（C2273 3→0 · S2 110→112）

**累计效果**：**L1 +18** · **S2 +11** · **总错误 −286** · **C2273/C2274 −162** ✓

**下轮入口**：按挂账交接表推进（CEffQuad 残留 · M7 lvar 族 · 双认领归属债 · adjudicate_lvar_type 接线 · ...）
