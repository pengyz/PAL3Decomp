# T4 迭代台账（2026-10-13 · pal3-converge · 迭代 4 收口）

**会话**：pal3-converge · **成员**：diagnoser（T29 收口，T6/T16/T25 等价）
**覆盖**：T26-T28 三任务（t28 pass 无需 repair）
**收口态基线**：S2 **121/209** · 总错误 **1372** · L1 **120** · matched **700/848** · partial 499 · L1 率 **120/619 = 19.4%**

---

## 一、本迭代裁决（Decisions）

### D1 · T26 C266x 逐个裁决（2 修 1 回退）
- **背景**：T17 预测 C266x 批可 +7 S2；T26 逐个 A 级证据裁决
- **裁决**：**逐个 A 级证据裁决**（禁批量推断）——2 修（NPC `CreateButton` sig 修正 + UIButton `SetLibFolder` cast）+ 1 回退（`rewrite_unqualified_member_call` 扩两形实链净负）
- **效果**：S2 118→**120** · L1 115→**120**（+5 字节全同函数）· 总错误 1383→1381（−2）
- **理由**：C266x 是聚合错误码（C2660 arity / C2664 param type / C2665 overload），机制各异；批量修必翻车
- **Confidence: high**（NPC sig 修正栈槽直证 + UIButton cast 字节等价 + 误判当场回退）

### D2 · T27 裸名方法 feed 通路 + 签名元数门（双因双修）
- **背景**：T26 挂账 ScriptPoolPage 两行（C2660 arity）——"调用形改写需裸名 feed 通路（宽 map 已证损伤、窄回退实测净负）"
- **裁决**：T27 **双因双修**：① 喂入修（`data.py` 补裸名方法入 `method_sigs`）② 元数门（`ast_transform` 三门齐：recv 仅 this / (name,元数) 唯一 / sig thiscall 非静态）
- **效果**：ScriptPoolPage **0 错回绿**（S2 120→**121**）· 总错误 1381→1372（−9）
- **理由**：T26 误判"查表键断"，T27 复核发现是"喂入断 + 查表键断"双因 ⇒ 单修任一无效
- **Confidence: high**（A 级 objdump：`0x41d1f2 mov ecx,esi + call 0x41c1e0` 无 push ⇒ thiscall 零实参；`0x41d1ff push 0x1 + mov ecx,esi + call 0x41c710` ⇒ thiscall 一实参）

### D3 · T26/T27 都有当场读抓误判 + 立即回退（诚实迭代纪律续）
- **T26**：`rewrite_unqualified_member_call` 扩两形单测 ✓ 但实链净负（+7）⇒ `git checkout` 全回退
- **T27**：首版无 recv 门 ⇒ 实链嵌套改写垃圾（CCBMagicWindow +102 等 3 单元、总 +241）⇒ 补「recv 仅 this」语义确定门后净正（−9）
- **教训**：**单测通过 ≠ 实链净正**（L1）；必须端到端验产物

### D4 · T28 双声称实测成立（pass 无需 repair）
- **T28 复核**：T26/T27 的声称（S2 +3 · L1 +5 · 总错误 −11）**当场读实测成立**
- **T28-O1-O4 非阻塞观察**：
  - **O1**：`stage2:110` 陈旧注记「裸名 feed 仍断」**已失实应删**（T27 已修）
  - **O2**：跨表同名同元数残余风险（`free_func_sigs` vs `method_sigs` 唯一门**不跨表**）—— **建议挂账**
  - **O3**：iter4 无归档快照 + `CLAUDE.md` 门禁数字待刷（T29 修）
  - **O4**：嵌套垃圾 1 例异路命中非 T27 面

---

## 二、本迭代教训（Lessons）

### L1 · 单测通过 ≠ 实链净正（T26/T27 都栽过）
- **症状**：`rewrite_unqualified_member_call` 扩两形单测 ✓ 但实链 +7；`recv` 门首版单测 ✓ 但实链 +241
- **规则**：**任何 codegen 改动必须端到端验产物**（`probe` 当场读），单测只能证"逻辑对"不能证"实链净正"

### L2 · 签名元数门三门齐（T27）
- **规则**：转换调用形必须三门齐：① recv 仅 `this`/`_this`（语义确定门）② (name, 元数) 唯一 ③ sig `__thiscall` 非静态
- **理由**：单门（如 name 唯一）不够——嵌套改写垃圾就是 recv 门缺失导致

### L3 · 双因双修（T27）
- **症状**：T26 挂账"调用形改写需裸名 feed 通路"；T27 复核发现是**双因**（喂入断 + 查表键断）
- **规则**：**复核发现"修不了"时，先问"是不是双因"**——单修任一无效

### L4 · 陈旧注记会失实（T28-O1）
- **症状**：`stage2:110` 注记「裸名 feed 仍断」在 T27 修后**已失实**
- **规则**：修 bug 后**必须回头清理相关注记**（否则下轮误导）

---

## 三、T28 的 O1-O4 非阻塞观察

| 编号 | 内容 | 处置 |
|---|---|---|
| **O1** | `stage2:110` 陈旧注记「裸名 feed 仍断」已失实应删 | **下轮清理** |
| **O2** | 跨表同名同元数残余风险（`free_func_sigs` vs `method_sigs` 唯一门**不跨表**）| **建议挂账**（独立轮）|
| **O3** | iter4 无归档快照 + `CLAUDE.md` 门禁数字待刷 | **T29 已修**（本任务）|
| **O4** | 嵌套垃圾 1 例异路命中非 T27 面 | 记录不阻塞 |

---

## 四、挂账交接（下轮）

| 项 | 归属 | 备注 |
|---|---|---|
| **O2** 跨表同名同元数残余风险 | codegen | `free_func_sigs` vs `method_sigs` 唯一门不跨表 |
| **O1** `stage2:110` 陈旧注记清理 | codegen | T27 已修，注记应删 |
| **T26** `MainPropUI` 两行 | annotation | 证据不足禁猜测 |
| **T22-F3** 三形守卫清点 647 行命中集 + 语义判定 | 独立轮 | |
| **T17 口径** 归属错批 E3 122（逐个 A 级）| annotation | 禁批量推断 |
| **T17** 354 条双认领 | 归属裁定 | |
| **T17** 233 个归属冲突 | 归属裁定 | |
| **T19** `adjudicate_lvar_type` 接线批 | codegen | |
| **T17** `UIPostUpdate`/`SRWR` 2 例 | annotation | |
| **T17** `FileSysDestory` typo | annotation | |
| **T17** `test_five_sites` 裸 glob | 存量 | |

---

## 五、迭代 4 效果对照（判据 v2.1 `aeb0adf41`）

| 指标 | 迭代 3 收口 | 迭代 4 收口 | Δ | 判据 |
|---|---|---|---|---|
| **L1 绝对数** ⭐ | 115 | **120** | **+5** | ✅ **主判据增长** |
| **S2 绿单元** | 118/209 | **121/209** | **+3** | ✅ |
| **总错误** | 1383 | **1372** | **−11** | ✅ |
| **matched** | 676/819 | **700/848** | **+24/+29** | ✅ 可测性解冻 |
| **partial** | 482 | 499 | +17 | 可测性解冻 |
| **L1 率**（参考）| 19.3% | **19.4%** | **+0.1pp** | ⚠️ 分母失真 |

**L1 率说明**：
- 分母（L1+partial）从 597 膨胀到 619（+3.7%），L1 率 +0.1pp
- **L1 绝对数 +5**（115→120，+4.3%）—— **主判据持续增长** ✓
- **19.4% 逼近 18-19.5% 平台上限**（离开平台需 ≥ 19.6%）—— **L1 增速 > partial 增速**（4.3% vs 3.5%）✓

**迭代 4 里程碑**：
- **L1 累计 +5**（115→120，T26+T27 贡献）
- **S2 绿 +3**（118→121）
- **总错误 −11**（1383→1372）
- **L1 率 +0.1pp**（19.3%→19.4%）—— **逼近平台上限**

---

## 六、验证证据（本 T29 收口）

| 项 | 命令 | 结果 |
|---|---|---|
| 全量 loop 端到端（含 export）| `python pipeline/cli.py loop --expect-s2 121/209 --expect-errors 1372 --expect-l1 120` | apply 0/9.8s · export 0/147.4s · codegen 1/186.4s（已归因：新失败 0 · 1 新增 C2664 同族 · `ScriptPoolPage.cpp` 已修复 · 净错误 −11）· S2 **121/209** ✓ · match 手动补齐 |
| 三基线刷新 | `regression_detector.py --save-baseline` + `compile_regression.py --update-baseline` + match 自动 | `baselines/20261013_082315.json`（209 文件 121 ok 88 fail）· `compile_baseline.json` 已更新 · `s4_baseline.json` stats: symbols=848 matched=700 L1=120 partial=499 |
| L1 当场读 | `python pipeline/cli.py match` | `matched 700/848 · L1 120 · partial 499 · L1 rate 120/619 = 19.4%` · `[L1 ratchet] previous 120 -> current 120` ✓ |
| CLAUDE.md:150 参数 | 编辑 | `--expect-s2 121/209 --expect-errors 1372 --expect-l1 120`（从 `118/209 · 1383 · 115`）|
| 当场读数（非事后基线）| `probe_census.json generated_at=2026-10-13T08:22:44` | S2 121/209 · 总错误 1372 |

**Confidence: high**（多轮端到端 + A 级二进制证据 + T26/T27 各自 verify grep + T28 pass 复核；code_gen rc=1 已逐条归因 = 新失败 0 · 1 新增 C2664 同族 · `ScriptPoolPage.cpp` 已修复 · 净 −11）

---

## 七、迭代 4 完成度总结

**T26→T28 三任务全部完成**：
- **T26**：C266x 逐个裁决 2 修 1 回退（S2 118→120 · L1 115→120）
- **T27**：裸名方法 feed 通路 + 签名元数门（S2 120→121 · `ScriptPoolPage` 回绿）
- **T28**：pass 无需 repair（双声称实测成立 + O1-O4 非阻塞观察）

**累计效果**：**L1 +5** · **S2 +3** · **总错误 −11** · **L1 率 +0.1pp**

**下轮入口**：按挂账 11 项推进（O2 跨表残余风险 · O1 陈旧注记清理 · T26 MainPropUI 两行 · T22-F3 三形守卫 · T17 归属错批 E3 122 · 354 双认领 · 233 归属冲突 · T19 adjudicate_lvar_type · UIPostUpdate/SRWR · FileSysDestory · test_five_sites）
