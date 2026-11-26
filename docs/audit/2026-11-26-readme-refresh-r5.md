# README 当前读数刷新（#9 落地后）+ 轮次状态表补 R5

- 卡：**#19 tsk_01M8C51MXHT818CY4R5M6H**（写面 `README.md` + `docs/audit/`）
- 观测时点：2026-11-26 22:44:46 – 22:46（本机）
- 并发状态：观测期间有管线在跑——22:38–22:43 一轮 loop（apply 19.5s / export 143.4s / codegen 197.3s / probe 87.3s，`failed=["probe"]`），22:44 起又有一个 `cli.py export` + `idat`（PID 110900/110901/110902）在跑。**本卡读数可能漂移**，以下每项都写明取自哪个产物、什么时间。

---

## §1 只读实测（本轮实跑）

### 1.1 `python3 pipeline/cli.py status`（22:44:46）

```
当前普查（data/status/probe_census.json）：
  S2 158/229 · 总错误 630 · 2026-11-26T22:41:53

⚠️ 基线"真相源"（三方互不相干，全部只读展示）：
  compile_baseline.json      S2 159/233  @ 2026-11-24T00:24:38
  baselines/latest.json      S2 900/995  @ 2026-11-26T19:16:35
  s4_baseline.json           L1 棘轮=189
  ⇒ ❌ 两份 S2 基线互相矛盾（159/233 vs 900/995）
  ❌ match → L1 棘轮（待测）记录 189 / 实况未知
```

直接读产物复核：`data/status/probe_census.json` → `s2.ok=158`、`s2.total=229`、`s2.fail_own=71`、错误行合计 **630**、`generated_at=2026-11-26T22:41:53`。
关键单元状态：`pal3/src/Misc/RoleStatePanel.cpp` **ok/0 错**、`pal3/src/Effect/ScreenEffectMgr.cpp` **ok/0 错**、`pal3/src/Misc/SaleUI.cpp` fail/33 错。

与 #4（README 旧值 157/229 · 633）的差：**+1 单元、−3 错误**，来自 RoleStatePanel 单元转 ok。同一读数在 `data/status/archive/probe_census_after_sefmgr_20261126.json`（`generated_at=22:10:49`）已是 158/229 · 630，两份失败单元集合**完全一致**（差集为空），说明该翻转发生在 22:10 之前，此后稳定。

### 1.2 `python3 pipeline/cli.py check`（22:44:50）

```
0 new errors + 36 frozen(advisory), 139 warnings — PASS
```

按 `WARN:` 前缀逐族计数（供参考，**不等于**汇总口径）：name_drift 40、functions 11、N20a 4、N22 1、N20b 1、N15 1；另有 `N13b` 141 条提示行。逐族计数之和（199）大于汇总 139，说明 check 的汇总不是按「WARN 行数」计数；本卡**不宣称已闭合构成**（见 §5-2）。
#4 记录为 `0 new + 37 frozen + 109 warnings`，本轮为 `36 frozen + 139 warnings`。

### 1.3 `git log -1` / `git status --short`（22:44:46）

```
$ git log --oneline -3
5b15fc482 docs(r5-saleui): 六池第二路径复核（IDA 文本清单 ??_L/??_M 双证，可 grep 复跑）+ 0x10564 索引语义与 0x3E08 数组基址两条旁证
4c41bd644 docs(r5-saleui): 独立对抗复核任务书（7 条可判定问题 + 只读纪律 + 交付格式）
e5cd8a187 docs(r5-saleui): 追加语料↔布局交叉校验（54/55 名可解析、6 处越界索引判定非布局错误）与 3 条既存问题上报
```

`git status --short` 中与本卡相关的只有 `M README.md`（本卡即将写）与 `?? docs/audit/`；其余为并发卡改动（`M data/annotations/structs/{RoleStatePanel,ScreenEffectMgr,UIFrameContainer}.json`、`M data/status/{adjudication_queue,evidence_ledger,pal3_registry.jsonl,s4_baseline,s4_diff_detail,s4_l1_identity_cur,struct_holes_20261125,vtable_transform_failures}`、`M docs/handoff/2026-11-26-struct-hole-campaign-handoff.md`、`M pipeline/gen/stages/stage5_fixup.py`、`M pipeline/_logs/loop_*.log` 等）。

### 1.4 L1（棘轮 189 / 最近可比 188 / 最近一次 run 38 不可比）

`data/status/s4_baseline.json` → `stats.match_L1=189`、`matched=1152/1259`、`carrier.paired=93`（文件被并发改动，但 L1 字段仍是 189，未重锚）。

`pipeline/_logs/loop_match.log`（**mtime 22:20:52**）尾部原样：

```
[L1 ratchet] previous 189 -> current 38
[L1 ratchet] semantic: previous 12 -> current 4 (L1+sem: 201 -> 42)
[L1 ratchet] population: previous matched=1152/1259 -> current matched=219/661
[L1 ratchet] coverage: previous carrier.paired=93 -> current 36
[L1 ratchet] ⚠️ 可比总体**已变化** ⇒ 两次 L1 不可直接比较；若确认可接受，用 `cli.py match --rebaseline "<理由>"` 显式重新对齐
[L1 ratchet] 🚨 L1 189→38 且 coverage 同降**且总体变化**——可能是真损失(单元蒸发/唯一定义源压制, 审计 C1a masking 场景)被洗成配对域; 拒绝自动对齐, 须显式 --rebaseline 并逐条归因
[L1 ratchet] 丢失函数 155 个(身份差分):
[L1 ratchet]   LOST ArcSceneObject::InitFromConfig(void) @5395648 size=87
...
[L1 ratchet] 新增 L1 4 个
[L1 ratchet] baseline+detail pair restored to previous run (ratchet may only advance explicitly)
[L1 ratchet] REGRESSION: byte-perfect functions lost — investigate before committing
```

解读（只陈述日志能支持的部分）：这次 run 的**符号总体从 1259 缩到 661**（matched 219），且可比明细从 **827 partial rows 缩到 121 rows / 47 units**（`s4_baseline.stats.partial=827` vs 该日志「121 partial rows in 47 units」），说明**大量单元根本没有进入对拍**，而不是一批函数字节同时变坏。棘轮据此判定「两次不可直接比较」，**拒绝自动对齐**并恢复基线与明细（`s4_baseline` 现为 `matched=1152/symbols=1262/L1=189/partial=827`），回归明细存档 `data/status/archive/s4_diff_detail_regressed_20261126T222052.json`。因此：

- 棘轮基线仍是 **189**（未被这次 run 改写）；
- **最近一次「可比」的实跑是 19:29 的 188**（已由 R4 归因到 `ac9c67673` 的 R3 改动，见 `docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md`）；
- 22:20 的 38 **不能当作退化结论**，也不能当作改善——总体蒸发的原因本卡只读未定谳（§5-1）。

### 1.5 结构体洞面（引用产物，不重跑 census）

本卡**不重跑** `census_struct_holes`：`data/status/` 的写面属 #15（ScreenEffectMgr 实施），且 22:44 起有 `export/idat` 在写 IDB，重跑会与并发卡抢产物。

引用工作树产物 `data/status/struct_holes_20261125.json`（**mtime 2026-11-26 22:12:22**，`_meta.rule` = v3 对齐感知+四修）：

| 口径 | 类数 | 洞数 | 洞字节 |
|---|---|---|---|
| HEAD 提交版（`git show HEAD:data/status/struct_holes_20261125.json`） | 201 | 1142 | 1,275,908 |
| 工作树现产物（22:12:22） | 201 | **1123** | **875,232** |

逐类差分（工作树 vs HEAD，全部 201 类里**只有 2 类变化**）：

| 类 | HEAD | 工作树 | Δ |
|---|---|---|---|
| ScreenEffectMgr | 2 洞 / 363,820 B | 3 洞 / **20 B** | −363,800 |
| SaleUI | 23 洞 / 44,560 B | 3 洞 / **7,684 B** | −36,876 |

对照任务给定口径：#9 三个提交（`7f9d6a636`/`b6f6b9385`/`e5cd8a187`）的洞面口径是 **1,239,032 B**，即 `1,275,908 − 36,876`，与上表 SaleUI 的 Δ **完全对上** ✓。工作树再减去 ScreenEffectMgr 的 363,800，即 875,232。
注意：`ScreenEffectMgr.json` 在 `git status` 里是 `M`（**未提交**），所以 875,232 是「工作树读数」，不是「已提交态读数」；`docs/handoff/r5-20261126/struct_holes_r5_20261126.json`（21:46:52）是 #9 自己的自检产物，时间早于 22:12，本卡只作旁证。

---

## §2 README「当前读数」刷新（前后对照）

### 刷新前（#4 于 20:56 写入，保留备追溯）

```
- S2 编译单元 **157/229** ok（fail 72，总错误 633）· L1 字节匹配 **188**（棘轮记录 189 未重锚，match 红=R4 首查项）· check **0 new + 37 frozen + 109 warnings — PASS**
- 结构体空洞：201 类 / 1142 洞 / 1,275,908 B（1246KB），产物 `data/status/struct_holes_20261125.json`
```

### 刷新后（22:46 写入）

- S2 **158/229** ok（fail 71，总错误 **630**，`probe_census` 22:41:53；RoleStatePanel 单元已 ok）
- L1 **棘轮 189 · 最近可比实跑 188（19:29，R4 已归因）**；22:20 一次 match 因可比总体蒸发（1259→661）被判不可比、读数 38 不作退化结论（详见本报告 §1.4）
- check **0 new + 36 frozen + 139 warnings — PASS**（22:44:50）
- 洞面：工作树 **201 类 / 1123 洞 / 875,232 B（855KB，产物 22:12:22）**；其中 #9 SaleUI 提交口径为 1,239,032 B（−36,876），差额 363,800 B 来自尚未提交的 ScreenEffectMgr 注解
- 旧值一行保留在「历史读数」里，不静默覆盖

---

## §3 轮次状态表（R1–R5 完成 + R6 挂账）

| 轮次 | 内容 | 提交 | 结果/证据 |
|---|---|---|---|
| R1 | CCBCamControl 池区全域闭合（+SkillUI 退赔） | `ed73fd85e`（11-26 11:49） | 洞 337,092B→12B（普查口径 357,092，提交文案的 337,092 为旧数，见交接文档修正注）；`docs/specs/2026-11-26-r1-*` |
| R2 | EquipUI 尾区九数组落位（+RoleStatePanel 七模块指针） | `cf70c0b48`（15:04） | 洞 164KB→15.6KB（168,244→15,960B）；`docs/specs/2026-11-26-r2-implementation-plan.md` |
| R3 | RoleStatePanel 40 员落位 | `ac9c67673`（18:40） | 洞 156,433B→556B；代价：RoleStatePanel.cpp L777 C2440 使单元 fail、L1 189→188（R4 归因） |
| R3.5 | 语义清理：7 类 42 员 `m_unk_<offset>` 统一形 | `22417d35d`（19:30） | 实迁 2 类（RSP 40 + EquipUI 2），`data/status/r35_semantic_cleanup_20261126.json` tally=42 |
| R4 | 0x4A2150 丢失归因 + ScreenEffectMgr 布局重建 | `e4378a1c4`（19:50，交接文档）；ScreenEffectMgr 注解在工作树未提交 | 归因报告 `docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md`；ScreenEffectMgr 洞 363,820B→20B（工作树产物 22:12:22） |
| R5 | SaleUI 池证据落位（首版，无 union） | `7f9d6a636`→`b6f6b9385`→`e5cd8a187`（21:49–21:57）+ 复核文档 `4c41bd644`/`5b15fc482` | 洞 44,560B→7,684B（−36,876B）；交付物 `docs/handoff/r5-20261126/` |
| R6 | 六项挂账（UITitle_JDHY/Note_Item、C2DSpark、CCBStage 三数字、PropUI 差 164、CCBRoleState ctor 写界、CCCTData 重铸） | 无提交（挂账） | 决策包 `docs/audit/2026-11-26-r6-backlog-dossier.md`；建议开工序 ⑥→⑤→①→③→②→④ |

---

## §4 一致性自检

- README 刷新后出现的每个数字来源：158/229·630 ← §1.1（`probe_census.json` 22:41:53）；189/188/38 ← §1.4；36 frozen·139 warnings ← §1.2；875,232/1123/201 ← §1.5（工作树产物 22:12:22）；1,239,032 ← §1.5 的 #9 口径推算（1,275,908−36,876）。均可在本报告定位。
- 与实况矛盾的**他人文档**（只列修正建议，本卡不改）：
  1. `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md` §1 的「158/189」仍把 R2 终点当现况；现值 158/229 · 630 / 棘轮 189·实跑 188。该文档已有 #10 的 5 条修正注，建议下次只追加「2026-11-26 22:44 读数」一行，不改原文。
  2. 同一文档「洞 1,275,908B」已被 #9（−36,876）与 ScreenEffectMgr（−363,800，未提交）两次推进，建议加注而不改史。
  3. `README.md` 自身旧值已在「历史读数」保留，未删除。

---

## §5 未决

1. **22:20 match 的「总体蒸发」未归因**：符号 1259→661、matched 1152→219、L1 189→38、partial rows 827→121（47 units）。「大量单元未进入对拍」比「155 个函数同时退化」更能解释这组数字，但成因未定——候选：对拍时对象/生成树不完整、或并发写 `pal3_registry.jsonl`；本卡只读无法证。需要一次**无并发**的干净 loop 到 match 复测才能定谳；建议开一张只读归因卡（或并入 R4 后续）。**在定谳前，README 不把 38 当退化、也不当改善。**
2. **check warnings 109→139 的构成未闭合**：逐族 `WARN:` 计数与汇总口径不一致（N13b 141 行但汇总 139），需要 check 的计数实现才能对账；本卡不宣称构成。
3. **875,232 依赖未提交改动**：`ScreenEffectMgr.json`（M）未提交，提交后洞面读数需复测；README 已注明「工作树读数」。
4. **并发期间读数可能再漂**：22:44 起又有 export/idat 在跑，`probe_census` 在下一轮 probe 后会被覆盖；本报告所有数字都绑定了观测时刻。

---

## §6 约束自证

- 只写 `README.md` 与 `docs/audit/`；未跑 `loop/apply/export/codegen/census` 等写盘项；未改 annotation/基线/生成树。
- 观测期间确实有并发管线（§1 抬头），已按要求注明「可能漂移 + 观测时刻」。
- `git status --short` 中本卡贡献：`M README.md`、`?? docs/audit/`。
