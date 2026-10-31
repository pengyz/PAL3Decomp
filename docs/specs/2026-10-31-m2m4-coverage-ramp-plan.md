# M2–M4 覆盖率爬坡方案 v2（对抗性复核修订版）

> 2026-10-31 v2 · v1 经双对抗复核（机制方 REJECT 15 条 / 可执行性方 ACCEPT-WITH-FIXES 13 条，
> 共 28 条发现）后整体修订。本版逐条销账（§8），未销条目不得开工。

## 0. 状态锚点（逐读数标注来源与时间戳）

| 读数 | 值 | 来源（文件@时间戳） | 口径 |
|---|---|---|---|
| 覆盖率分子/分母 | **124/213** | `data/status/probe_census.json` @2026-10-26T01:21 | S2 真身（单元级） |
| S2 基线（对照） | 135/214 | `compile_baseline.json` @2026-10-30T19:57 + `baselines/latest.json`（两份互恰） | 与 census **非同一测量**（见 D0） |
| L1（三限定） | 161（棘轮记录值，实况待 Linux） | `s4_baseline.json` | 截断/等长/reloc don't-care |
| rsite 分账 | ok 92 · class_ok 319 · self_local 13 · mismatch 1 · **unresolved 3** · unaligned 6650 = 7078 | `s4_baseline.json`（现值） | R2a-4 修复后**预测** ok 95/unresolved 0——D6 实跑若仍 92/3 判「门未生效」，非读数漂移 |
| 链接 | 闭合（PAL3_mocklink.exe 471040B） | mock_link 实测 | unresolved 0 |
| PRUNED 债 | 28 项（15 函数 + 13 数据） | 9 个 stub 的 // PRUNED 段（迁移后 = `data/status/pruned_debt.json`） | 函数项中仅 3 件零证据可快胜 |
| S2-fail 错误 | 1116（census 口径）/ 1110（基线口径） | 同上两源 | **D0 归一后单一**；C1003 截断单元 2 个（free_functions/CCBStage 各 101 条）按最大行号记进展 |

⚠️ **口径纪律**：覆盖率 = 单元级 S2 真身口径，禁外推「代码完成度」；L1 三限定随数字走；
stub 空体符号数不等于真身函数数；C1003 截断单元错误数不可比、最大行号才是进展。

## 1. D0（开工前置）：读数归一 + 机制三修

**D0-1 读数归一（Linux 窗口首件）**：跑一次 `apply→export→codegen→probe` 归一三读数；
census（10-26, 213/124）与基线（10-30, 214/135）的 **13 个分止单元逐个归因**（12 修复 / 1 回退 SceneVisNode / 1 new_unit CG_Entry）落账；
m4_ratchet 锚定**唯一 census 四元组**（generated_at + unit-set hash + ok 绝对数 + 分母）；
分母变动必须走 `--rebaseline "<理由>"` 归因口（仿 `pipeline/link_probe.py` 棘轮）；
`loop --expect-errors` 锚统一为归一后单值。Linux 不可得 ⇒ 冻结读数轴判决（§2.2 降级判据），机制轴继续。

**D0-2 机制三修（Windows 可做，先行）**：
1. **退役复活闸**（R1-F2）：`demand_ledger.txt` 状态化（`active|retired` 行）+ 持久 `phase2/stubs/_supply/exclude.txt`；
   `generate_supply_from_log` 生成前做**已定义面普查**（复用 haystack 机制）+ honor retired/exclude；
   「退役 = ledger 标 retired + supply 重生成 + mock_link 回归」原子步。
2. **`_real/` 进编译面**（R1-F1）：mock_link extras 增 `glob('_real/*.cpp')`；显式声明与母设计 §6 M2
   「stub TU 内嵌」的偏离（独立 `_real/` 面 = 真函数回填专用，防 AUTO-GENERATED 再生成灭失 R1-F7）。
3. **债账迁址**（R1-F7）：PRUNED 28 项 → `data/status/pruned_debt.json`（stub 内注记仅镜像）；
   再生成保护：手修一律「修提取器+再生成」（R11）或侧车补丁；**禁止直改 AUTO-GENERATED 面**。

## 2. M3：stub↔S2 退役对账（规则改名 S1–S4，消标签双义）

**盘点口径表（先钉死，R1-F12 / R2-F10）**：

| 路径模式 | 类别 | 计入 R3 存量？ | 退役动作 |
|---|---|---|---|
| `phase2/stubs/*_stub.cpp`（平层，=单元 stub） | unit | ✓（主口径） | 删文件 |
| `phase2/stubs/_slots/**` | slots | ✓（符号口径） | 剔条目 |
| `phase2/stubs/_supply/**` | supply | ✓（符号口径） | ledger retired + 重生成 |
| `phase2/stubs/_eh_metadata_stub.cpp` | glue | ✗（恒存） | — |
| `phase2/stubs/_real/**` | real | ✗（真函数面） | 转正入真身 |
| `**/*.obj`（编译产物） | 排除 | ✗ | 移出源码树（D0-2 附带） |

| 规则 | 判据 | 动作 |
|---|---|---|
| S1 催删 | S2-ok 单元仍有 unit stub | WARN + 计 retire_due；`--strict` 或存量阈值 ⇒ exit 1（R1-F13） |
| S2 催建 | S2-fail 单元缺 unit stub | FAIL-LOUD |
| S3 双口径棘轮 | 单元数 + 全 stub 面符号总数（`stub_function_spans` 复算）**非增**；一切变动带归因（enum：`retire/new_unit/regression/census_refresh/rebaseline`） | 无归因增长 ⇒ exit 1（R1-F5/F6 / R2-F5） |
| S4 读数 | 覆盖率（census 四元组口径）+ 存量 + retire_due 入 `cli.py status` | 只读展示 |

**retire 语义（R2-F9）**：v1 `retire --plan` 只打印建议清单；实删 = 人工执行 + mock_link 闭合回归 + git 追踪面确认。
**台账写者/执行者（R1-F15）**：写者 = `stub_retire.py record`（append-only，改写历史检出用例）；执行者 = M4 轮次流程。

## 3. M4：爬坡迭代循环（v2 修订）

### 3.1 靶源（优先序显式，去重归属单一）

| 序 | 靶源 | 量 | 备注 |
|---|---|---|---|
| T1a 零证据快胜 | ArraySort/CreateProtectedObj（PRUNED 函数）+ 数据残留 13 件 | **16 件**（R2-F4 修正，非 28） | byte_592DA4 等 3 件划 T3，不双计 |
| T2 pending 裁决 | `data/status/pending/` **名单落台账**（实测 20 个 review_*.md + 归属/缺口 JSON 队列，逐件判据+验收，R2-F8） | 20+ | 限期裁决 |
| T3 注解债 | 双源数据 3 件 · `InitEffClass`（no_decomp）· F70 残余 5 件（gbLightObj×4/gbOBBox）· dllimport 误标普查 | ~10 | F70 五件**单靶源归属** |
| T4 错误族清偿 | 89 fail 单元 / 1116 错（**27 个单错单元 = 快胜池**；top 族 C2440 257/C2664 192/C2039 84/C2065 75） | 主战场 | **配额：每 3 轮至少 1 轮 T4**（R1-F10） |
| T5 FDS N=1 | 33 件（台账逐件补实名/验收列，R2-F11） | 33 | 与 T4 合流 |

### 3.2 循环体与验证链（含 v1 缺口修复）

```
①选靶（§3.1 序）→ ②病灶层检查 → ③修复（修提取器+再生成/annotation）→
④验证链 → ⑤[S2 转 ok ⇒ 删 stub]（前置：同轮 probe 当场读该单元 ok——R1-F8；
   Linux 不可得时 ⑤ 挂批级边界，不得凭陈旧 census 删）→ ⑥mock_link 闭合回归 →
⑦轮级轻量 L1 抽查（touched 函数，R1-F9）→ ⑧三读数+归因落账（append-only）→ commit
```

| 验证步 | Windows（每轮） | Linux（批级） |
|---|---|---|
| 修复后 | pytest **已知失败集不增**（见 §4）+ `cli.py check` | `apply→export→codegen→probe` |
| 删 stub 后 | `stub_retire.py check` + `mock_link.py` 必闭合 | — |
| 轮级 | 轻量 L1 抽查（touched 函数三限定） | — |
| 批级 | — | `loop --expect-*` + `match` 终验（含 R2a-4 rsite 分账**结构对上+偏差归因**，R1-F9） |

**回退粒度（R1-F9）**：以 commit 为单位回退；破闭合立即回退该轮；census/ledger/ratchet 为 append/状态化写入，避免整文件重写冲突。
**停滞升级（R1-F10）**：多指标（S2 ok / errors 总数 / PRUNED 清偿 / retire_due）任一无进展计 1 轮，连续 3 轮 ⇒ 升级为 **pending 限期裁决**（不是扩员缓兵）。
**禁注水机械化（R1-F11）**：覆盖率分子只认 census ok；函数级宣称必带对拍读数（match/partial）；归因 JSON schema（enum + evidence：census_diff/round_id/commit_sha）。

### 3.3 M2 拆两件（R2-F2/F10）

**M2a 对拍机制三限定化（先行）**：新对拍面 = **mock_link 产物**（LINK `/MAP` + obj 字节），
判据复用 `pipeline/compare_pal3.py` + `tools/gbengine_compare.py`（截断-to-size/等长/reloc don't-care），
输出 match/partial 判定 + 三分账，**废除** `manual_l1_match.py` 的 WINDOW=0x100/similarity 口径（其编译面为已冻结 manual/ 产物 = 验证空气，R1-F3/R2-F2）。
**M2b WinMain 真身回填**：素材 = `manual/pal3/error/free_functions.cpp:30668`（v1 的 :26843 引用错误，实测为 RoleAtt 函数体；pal3/src 无 WinMain 段）；
落 `phase2/stubs/_real/WinMain_real.cpp`（进编译面，D0-2）；`_WinMain@16` 合成条目经 ledger retired 原子退役；
验收 = 链接闭合 + 对拍判定（match/partial 如实）+ 三限定三分账落账。

## 4. 测试基线口径（R2-F3 实测修正）

Windows 实测：**57 failed + 15 collection errors**（非 v1 所称 20+1；含真回归——如
`test_global_region_audit` 崩溃 + 数据漂移断言）。口径改为：
- **known-fail 清单**（`data/status/known_fail_windows.json`）：环境失败 / 真回归 / 断链三桶；
- 门禁 = **失败集不增**（对照清单），不是「绿」；
- 验证链显式 `PYTHONUTF8=1`（GBK 默认另炸 3 收集 + cli status）；
- `pipeline/ida/_archive/test_*` ×14 显式 `--ignore`；
- 真回归桶先修或挂账（`test_global_region_audit` 两件挂账 T2）。

## 5. C1003 截断盲区（R2-F7 补入 §0 口径 + 度量）

free_functions.cpp / CCBStage.cpp 各 101 条错误 = 截断面（修 9 露 9 型）；
二单元进展判据 = **列表内最大行号前进**（CLAUDE.md 度量盲区条）；
M2b 在 free_functions 上的交叉影响：WinMain 回填面（_real/）与截断面解耦，但 PRUNED 债（ArraySort 等）在该单元 ⇒ T1a 与 M4 同轮协调。

## 6. D0–D8 交付物（修订工期，R2-F10）

| # | 交付 | 前置 | 量级 | 验收 |
|---|---|---|---|---|
| D0-2 | 机制三修（退役复活闸/`_real` 编译面/债账迁址） | — | 1 天 | 再生成不灭失手修（用例）· 退役不复活（用例） |
| D0-1 | 读数归一 + 13 分止单元归因 | **Linux 窗口** | 0.5 天 | census 四元组锚定 + 归因落账 |
| D1 | `tools/stub_retire.py`（S1-S4 + 盘点口径表） | D0-2 | 1 天 | 分类规则表 + 篡改实验（含分母缩水/rebase 无归因 FAIL） |
| D2 | `cli.py status` 三读数接入 | D1 | 0.5 天 | 只读展示 |
| D3 | `m4_ratchet.json` 台账（append-only + 归因 schema） | D1 | 0.5 天 | 改写历史检出用例 |
| D4 | M4 首批 ≥3 轮（T1a 快胜 + T3 ≥1 + T4 ≥1） | D0-2,D1-D3 | 持续 | 每轮三读数+归因+闭合 |
| D5a | 对拍机制三限定化（mock_link 产物） | D0-2 | 1 天 | 判定+三分账 |
| D5b | WinMain 真身回填 | D5a | 1 天 | 闭合+对拍账 |
| D6 | Linux 批（R2a-4 match 终验 + loop 断言） | D0-1 | 0.5 天 | rsite 结构对上+偏差归因 |

## 7. 风险与降级（含 R2-F6）

| 风险 | 对策 |
|---|---|
| Linux 窗口长期不可得 | **降级判据**：冻结读数轴（ratchet 不判决）、机制轴继续（D0-2/D1/D2/D3/D5a）、每轮 mock_link+pytest+轻量 L1 抽查为验证底；D6 前置「至少一次 Linux 冒烟批」后 D4 才放行删 stub 步⑤ |
| 删 stub 破链 | mock_link 回归必跑，破则回补（记 `regression` 归因 + 负债事件） |
| 双副本漂移 | stub 不进 S2 分母（铁律）+ 退役即删 + S3 双口径 |
| 度量造假 | 分子只认 census · 四元组锚定 · append-only · 篡改用例 |

## 8. 复核销账表（28 条 → 本版落点）

| 来源 | 发现 | 落点 |
|---|---|---|
| R1-F1 | `_real/` 不进编译面 | §1 D0-2.2 + D5b |
| R1-F2 | 退役复活/双定义震荡 | §1 D0-2.1（ledger 状态化+已定义面普查+原子退役） |
| R1-F3 | 对拍作用于冻结产物 | §3.3 M2a（mock_link 产物+三限定） |
| R1-F4 | 锚点矛盾/census 无新鲜度门 | §0 逐读数标源 + D0-1 四元组 + 新鲜度校验 |
| R1-F5 | 单调口径被自家对策证伪 | §2 S3「非增+归因」+ 负债事件 |
| R1-F6 | 存量可掏空稀释 | §2 S3 双口径（单元+符号） |
| R1-F7 | 手修无保护/债账蒸发 | §1 D0-2.3（债账迁址+禁直改+R11） |
| R1-F8 | ⑤前置不在验证链 | §3.2 ⑤ 前置写死 |
| R1-F9 | 轮级验证缺 L1/回退粒度 | §3.2 轻量 L1 + commit 粒度 + D6 结构对上 |
| R1-F10 | 停滞判据错位 | §3.2 多指标 + 限期裁决 + T4 配额 |
| R1-F11 | 红线不可证伪/归因零约束 | §3.2 机械化判据 + 归因 schema + append-only |
| R1-F12 | 盘点口径未定义 | §2 盘点口径表 + .obj 移出 |
| R1-F13 | S1 只 WARN | §2 S1 strict/阈值 |
| R1-F14 | 标签双义/裸引用 | S1-S4 改名 + 引用带路径 |
| R1-F15 | D1-D3 依赖倒置 | §6 顺序 + 写者/执行者点名 |
| R2-F1 | 双快照漂移（13 分止单元） | D0-1 归一 + 四元组 + --rebaseline |
| R2-F2 | 对拍链三重断裂+素材双错 | M2a 重造 + 素材 :30668 修正 |
| R2-F3 | 测试口径失实（57+15） | §4 known-fail 三桶 + 失败集不增 |
| R2-F4 | T1 快胜 28→16 | §3.1 T1a 16 件 + 归属去重 |
| R2-F5 | 棘轮三口径漂移 | §2 S3 双口径 + 四元组 + WinMain 个案记账 |
| R2-F6 | Linux 单点依赖 | §7 降级判据 + D6 前置 |
| R2-F7 | C1003 盲区缺位 | §5 专节 + 最大行号读数 |
| R2-F8 | pending 20 不可复核 | §3.1 T2 名单落台账 |
| R2-F9 | M3 自相矛盾/retire 语义 | §2 retire 语义 + S1-S4 |
| R2-F10 | 工期低估 | §6 修正（D5 拆 a/b） |
| R2-F11 | FDS 台账占位/口径分叉 | §3.1 T5 补实名 + 统一三限定口径 |
| R2-F12 | 数字无出处 | §0 删 3435 引用，计数以 `stub_gen --count` 复算 |
| R2-F13 | 预测 vs 现值 | §0 rsite 行标注 + D6 判定规则 |
