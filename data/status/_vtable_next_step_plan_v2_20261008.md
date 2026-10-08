# vtable 架构下一步方案（v2 —— 经 4 路对抗复核后重写）

**日期**：2026-10-08
**状态**：v2，**经 4 路对抗复核**（`dda85150` /GR · `188399ad` 时序 · `a453229e` 重复建设 · `6135eb20` 验收）
**v1 结论**：**基本被推翻** —— 见 §1「被证伪的 v1 主张」

---

## 1. 被证伪的 v1 主张（诚实记录）

| # | v1 主张 | 判决 | 证据 |
|---|---|---|---|
| 1 | F6 基线 **S2 87 / L1 53 / errors 1975** | ❌ **严重错误（陈旧 145 提交）** | 权威物实测 **S2 108/209**（`baselines/latest.json` 2026-10-06）· **L1 94**（`s4_baseline.json.stats.match_L1`）· **errors 1515**。F6 三数唯一命中 `_d1_ledger.md:3742`（2026-09-25 批次 W 历史行）|
| 2 | 「阶段 1(`/GR`) 是阶段 2(T3) 的前提」 | ❌ **三重证伪** | T3 缺陷**全在二进制侧、0 次编译**：raw 1164 vs 族判据 511，**109/189 表被截，109/109 全由族判据造成**，丢 653 槽；带 /GR 时双裁判逐槽结论**逐字相同**（仅多 1 条确定性 `address_point_rtti`）|
| 3 | F1「`/GR` 是结构性阻塞」作为**通则** | ❌ **证伪** | 二进制自身有 **5 张带 COL 的真表**：`0x570A78`(`length_error`)/`0x570A98`(`logic_error`)/`0x570AA8`(`out_of_range`)/`0x5731D4`(`type_info`)/`0x573238`(`exception`)；结构验证为 VC6 `_RTTICompleteObjectLocator` |
| 4 | 「移除 `/GR` ⇒ `.rdata` 可 byte-match」 | ❌ **证伪（必要非充分）** | `AStarPathFinder` 自身即反例：二进制 **3 槽** vs 编译产物 **2 槽**（`AStarPathFinder.h:38 ~AStarPathFinder();` **非 virtual**，二进制 slot0 是虚析构）|
| 5 | 阶段-1 验收「S2/L1/errors 不劣于基线」 | ❌ **恒真、无判别力** | `compare_pal3.text_bytes` **只含 `.text`**；/GR 对 `.text` **零影响**（79 TU 逐字节 identical）|
| 6 | 阶段-1 验收「`.rdata` 非零逐槽一致率」 | ❌ **无判别力** | 实测基线（不移除 /GR）逐槽一致率 **全 0.0%**（0/7、0/8、0/1…）；成因是族判据截断 + obj 槽0 是删除析构 + COL，**与 /GR 无因果** |
| 7 | 阶段-2 验收「族判据 ≈ raw」 | ❌ **方向相反、会假绿** | `idx={}` 时天然满足（511→1164）⇒ **删掉唯一阻挡跨类渗漏的信号**；`CEffectSystem` 注解实测 **9 槽**（slot8=`0x004C6260`），e2e 钉 8 是**固化截断**；raw 自身在 **77/189** 表被截 ⇒ raw 也是下界 |
| 8 | 「raw 1164 作稳定分母」 | ⚠️ **稳定但不可靠** | 稳定（3 次 hash 一致；idx 改 {} / 砍半 / 全改名，raw 逐位不变）；但**过度界定有反例**：`0x56F9DC` raw=15 含 **6 个类族**；**101/187 张 raw 表含 ≥3 类族** |
| 9 | 阶段-3「`_layout_asserts.h` 已验证 `wired_and_enforced`」 | ❌ **夹具自证** | `pal3/src/_layout_asserts.h` **不存在**；`grep -rn _layout_asserts.h pipeline/` = **0 命中**；`wiring_decision` 是 `tests/test_vtable_e2e.py:342` 的**纯函数**，测的是**临时目录头**（`:970`）⇒ T2 是**从零接线** |
| 10 | 「接入 `gate_registry`」 | ❌ **范畴错误** | `grep -rn "gate_registry\|genericity_layering" --include=*.py --include=pre-commit .` = **空** ⇒ 两者是**纯 Markdown、零代码读取** |
| 11 | 「`tools/vtable_call_transform.py` 是本会话 v1 死代码」 | ❌ **归属错误** | `git log -1 a033c4a5c` = 2026-09-24 16:32，且是分叉点 `ca3773606` 的**祖先**（前序 vtable 会话遗留）**但"债"判定成立且更重**（见 §4）|
| 12 | 「与远端口径需对齐」 | ❌ **错方向** | `vtable_verify` 读 .obj+镜像、**从不读 `vtables[].slots`**；`vtable_slot_audit` 只读注解+缓存、**从不读镜像** ⇒ **无共同分母**，构造上互补 |
| 13 | 依赖图 | ⚠️ **缺 5 条 · 假 2 条 · 0 环** | 见 §3 |
| 14 | 方案无回退路径 | ⚠️ **缺失** | 已补 3 级（§6）|

---

## 2. 更正后的事实表

### 2.1 权威基线（**三个 S2 源互不相等，分母都不同**）

| 来源 | S2 | 总错误 | L1 | 时间 | 备注 |
|---|---|---|---|---|---|
| `compile_baseline.json` | 108/209 | — | — | 2026-10-06T19:03 | — |
| **`baselines/latest.json`** | **108/209** | **1515** | — | 2026-10-06T22:27 | `_authority="单一权威 2026-10-07"` |
| `probe_census.json` | **79/204** | **1996** | — | **2026-09-24** | ← **`--expect-*` 实际比的就是它**（13 天前）|
| `s4_baseline.json` | — | — | **94** | — | `flags` **含 /GR** |

⚠️ **棘轮会回写基线**：`cli.py:677` 读 `prev_l1`；`:733-743` 退化时把 `prev_text` 写回 ⇒ **文件恒 = max(历史最好, 本次)** ⇒ **事后读文件必判 PASS**。

### 2.2 关键判词数字（可直接当回归基线）

```
raw=1164  fam=511  tables=187  family_break_not_at_target=109
obj vtables=28  with_COL=28  obj slots=615
配对全等表数 = 0/9 类      （今天全 FAIL）
C1003 max line = 3838 / 2849
layout_assert_gen total=10837  active=140
```

### 2.3 已证实的事实

| 事实 | 证据 |
|---|---|
| **移除 `/GR` 编译安全** | 全仓 `dynamic_cast`/`typeid` **0 命中**；79 TU 两模式都成功 / 125 都失败 / **0 不对称** / 无 C4541 |
| **游戏类 0 张表带 COL**；5 张带 COL 的全是 CRT/STL | 189 张 ctor 实写表；`.?AV` 6 条全 CRT/STL，`.?AU` 0 条 |
| **移除 `/GR` 不破坏那 5 张** | `libcpmt.lib` 的 /GR 副本在链接期胜出（`??_7out_of_range@std@@6B@ from libcpmt:string.obj`）|
| **`/GR` 除 COL 外零影响** | `.text` 逐字节 identical **79/79**；非 RTTI `.rdata` 尺寸 `{+4:28, 0:133}`；段 characteristics 同 `0x40301040` |
| **`/GR` 指纹 = 含 COL 的表数** | 今天 **28/28**（`--list --json` 可读）；A/B：`col_gr.obj ap=4 col=??_R4B@@6B@` vs `col_nogr.obj ap=0 col=None` |

---

## 3. 依赖图（修正后）

```
阶段 0（前置）: 跑一次 merge 后的 loop ⇒ 建立**本地终态**基线
                 （本会话 32 提交从未跑管线；probe_census.json = 2026-09-24）

                 ┌─ [T3] 表长界定口径（vtable_verify + vtable_compare **同改**）
                 │       + tests/test_vtable_e2e.py:1224/:1659-1660 钉值
                 │       + 注解 oracle vtables[].slots（94 表）
                 ├─ [T4] 发射器/注解槽序（UI3DCtrl/CEffectSystem/CGameData）
                 ├─ [T2] _layout_asserts.h **从零接线**（emit_headers.py + include 块）
                 └─ [T1-spike] 全库量化（只读，产物落 /tmp）
   最大并行集 = {T3, T4, T2, T1-spike}
                 │
                 └──► [T1-landing] 移除 4 处 /GR + --rebaseline + L1 重测
   关键路径 = T3 → (T2‖T4) → T1-landing
```

**真边**：`T3 → vtable_verify + vtable_compare 必须同改`（parity 测试 `tests/test_vtable_verify.py:466-491`）

**缺失 5 条**（v1 漏）：
1. `T3 → tests/test_vtable_e2e.py:1224`（`bin_slots==8`）+ `:1659-1660`（`hard_end_slots==8`）钉值
2. `T3 → 注解 oracle vtables[].slots`（94 表，被 `vtable_decl_check.py:221-224,1229` 的单调分量 `slots` 钉住）
3. **阶段 0 基线**（v1 完全没有）
4. `T2 ↔ T4` **同文件** `pipeline/gen/stages/emit_headers.py`（T4 `:2411-2585`；include 块 `:1554-1700`）⇒ 必须串行落 commit
5. `T4 → decl_check 棘轮`（条件边：仅当增删 `vtables[].slots`）

**虚假 2 条**（v1 误列）：① `T1 → T3` ② `T3 → 远端 vtable_slot_audit 口径`（该工具无任何二进制边界代码）

**⚠️ T3 会打破的现有钉值**（v1 未提，task-8 §12 自列为 tripwire）：
- `tests/test_vtable_verify.py:1399` 的 `raw_slots >= 1000`
- `tests/test_vtable_e2e.py` 的 `raw == 1164`

---

## 4. 必须先做的**决策**（非"整合"）

远端的「三分法」不能当权威：`genericity_layering.md` **只命名 52/90 工具**，38 个未分类（含本地 6 个），文件 `:38` 自认"待分 ~60 件"，而 ledger 写"✅三分法**全工具**" ⇒ **42% 未分类**。且远端分类与**自身清理判据**（`workflow_review.md:25`「死闸零引用⇒退役」）自相矛盾。

### 决策点 D1：`vtable_decl_check` vs `vtable_mapper`（**二选一**）

| 项 | 远端 `vtable_mapper` | 本地 `vtable_decl_check` |
|---|---|---|
| 生产接线 | ✅ `check_annotations.py:752-760` + `:770-789` 棘轮 | ❌ **零生产消费者**（grep 空）|
| 签名校验 | ❌ **死统计**（`vtable_mapper.py:57` 初始化后从不 `+=`/print，docstring 却承诺）| ✅ 三分量（槽数/真槽序/签名）|
| 真槽序 | ❌ 无（只有"前一槽未解析则报 order_mismatch"弱代理）| ✅ |

⇒ **二选一**：① 把 `decl_check` 接进 `check_annotations.py` 接管签名/槽序分量；或 ② 把缺失分量补进 `mapper` 后退役 `decl_check`。
⚠️ **若 X2「整合」被理解为"砍重复"，会砍掉唯一覆盖签名/槽序的实现**。

### 决策点 D2：重复实现收敛

| 对 | 判定 | 建议 |
|---|---|---|
| `vtable_verify` ↔ `vtable_compare` | **重复**（自认"逐字同规则"，有 parity 测试）| 提为单一实现 + 注入适配器 |
| `vtable_sig_infer`+`decl_check` ↔ `vtable_slot_audit` | **重复/口径冲突**（raw 字节 vs 提交缓存 `_ret_n_batch.json`，**无 parity 测试**）| 定 `sig_infer` 为唯一证据源 |
| `vtable_scanner` ↔ 两份 `bin_table` | **冲突**（其终止判据被 `vtable_compare` docstring 自认失效：`CEffAction` 读 96 槽）| 退役或复用同一界定 |
| 远端 `detect/fix_vtable_splits`·`fix_all_vtables`·`apply_vtable_fix`·`vtable_class_reconcile` | **重复**（5 件同题）| 远端内部收敛 1 检测 + 1 应用 |
| `vtable_slot_order`·`slot_classifier`·`layout_assert_gen` | **互补**（远端无对应）| 保留；`layout_assert_gen` **必须先接线** |
| `coff_vtable` | **互补** | 保留 |

### 决策点 D3：立即清理（低成本、高收益）

1. **`tools/vtable_call_transform.py` 废弃/归档** —— 实测比记录更重：
   - `--dry-run` = **`Total: 0 transforms`**
   - 在**自己 docstring 的形状**上输出**非法 C++**（`Step B` 的 `[^)]*` 跨不过 cast 嵌套括号 ⇒ 旧 cast 前缀永不剥除，**括号不平衡**）
   - **默认写盘**（`dry_run = '--dry-run' in sys.argv`，无 argparse），命中 `data/status/_tools_argparse_hazard.json` **自己的判据**却不在名单（该扫描 2026-09-20，**早于工具创建** 09-24，**从未重跑**）
2. **`tests/test_vtable_call_transform.py` 改名** —— 它测的是 `stage3_cleanup`，与同名的死工具**无关**；撞名把死工具从 grep 里藏起来了
3. **修远端 `vtable_slot_audit.py:107`** —— `rets.get(addr)` 无归一（`:55-62` methods 却用 4 变体）⇒ **4 个有 `[4]` 证据的槽被误报 `evidence-none`**（10 个槽地址是小写 hex）

### 决策点 D4：SDD 文件入库位置（v1 遗留）

本地 32 提交含 **17 个 force-add 的 SDD 文件**（`progress.md` + 8 brief + 8 report），远端惯例是 `.superpowers/` **不入库**、durable 台账放 `data/status/`。
⇒ 建议 **移到 `data/status/`**（与远端 `architecture_governance_ledger.md` 同址）。

---

## 5. 修正后的方案（X1′）

### 阶段 0（前置）：建立本地终态基线
- 跑一次 merge 后的 `loop`，**同一次运行内当场读 stdout**
- 加 **flags 一致性前置断言**
- 记录：S2 / L1 / errors 三元组 + C1003 两个截断单元最大行号

### 阶段 1：T3 表长界定口径（**关键路径起点**）
- **两侧同改** `vtable_verify.bin_table_from_image` + `vtable_compare.bin_table`
- **真实边界**：ctor 实写目标落在当前表**内部**时截短（`CEffectSystem 0x56F824` 9→8）
  - ⚠️ **不是**「`nxt[0]` 未排序」（`bin_vptr_targets()` 返回 `sorted(out)`，该表述已撤销）
- **修正的验收判据**：`family_break_not_at_target == 0`（今天 **109**）—— 断裂点必须落在 `targets` 上
- 同步更新被打破的钉值（`test_vtable_verify.py:1399`、`test_vtable_e2e.py` 的 `raw==1164`、e2e 的 `==8`）

### 阶段 2（并行）：T4 发射器槽序 + T2 接线 + T1-spike
- **T4**：UI3DCtrl 根因（抄基类 21 槽 + `slot_0` 未识别为覆写）+ CEffectSystem（`Reset` `ordinal=8` 却排第 2 位）+ CGameData（**重复注入**虚析构）
- **T2**：`_layout_asserts.h` **从零接线**（`emit_headers.py` 无任何 `_layout_asserts` 引用）
  - 验收：接线存在性 `grep ≥ 1` + 正相 rc0 + 负相 C2118 + 上报 active 覆盖率
  - 一般化：**全部配对类 `obj_count == raw_bin_count`**（今天 **9 类 / 17 项全 FAIL**）；`26→8` 仅作单点例证
  - ⚠️ `probe_compile.py:256` 会 `rmtree(/tmp/pal3_probe)` ⇒ 必须在 `match` 之后、下一次 `probe` 之前跑
- **T1-spike**：全库量化（只读，`/tmp`）+ `.text` 逐字节 diff 控制实验

### 阶段 3：T1-landing（**后置**）
- 移除 4 处 `/GR`：`cmake/MSVCSettings.cmake:89` · `pipeline/compare.py:69` · `:81` · `pipeline/cli.py:690`
  - 另 `tools/vtable_verify.py:161 DEFAULT_PROBE_FLAGS`（否则 obj 侧 COL 会被报成偏差）
  - 另注：探针 flags 用 `/MD` 而 `build.ninja` 用 `/MT`（`compare.py:69,81`、`cli.py:690` 同病）
- **必须 `--rebaseline`**：换 flags 后 `pop_changed` 只 print 警告（`cli.py:715-718`），`:733` 的 exit 1 仍会触发 ⇒ L1 必硬红
- 记 population；L1 基线**须重测**

### 贯穿：门禁接入（**有前提**）
⚠️ **直接接线会得恒绿静默门禁**：`PAL3_E2E_LIVE` 未设时 `python3 tests/test_vtable_e2e.py` → `22 passed / 8 skipped`，**exit 0**，8 条真裁判**全 SKIP**（而 `PAL3.exe`/`wine_cl.sh` **都存在**）⇒ 正是本仓自点名的反模式（`task-5 R=1 Q2`「门禁永久静默关闭」、`workflow_review.md:25` 死闸）。
⇒ 接入前必须：**fail-closed 策略**（缺 env ⇒ 红，而非 SKIP）+ 决定挂哪条链（真机路径要 wine 编译，**不适合 commit 钩子**）。

---

## 6. 回退路径（v1 缺失）

| 级 | 动作 |
|---|---|
| **零级** | 控制实验：同单元有/无 `/GR` 双编译 + `.text` 全节逐字节 diff。**若相同，则任何 S2/L1 变化不得归因于 `/GR`** |
| **一级** | `git revert` 4 处字面量（F3 已核，无数据面残留）|
| **二级** | 保留生产 `/GR`，只把 `vtable_verify.py:161` 改 `('/Od',)`，把 `address_point_rtti` 登记为**预期偏差**（`test_vtable_e2e.py:329-332` 已写好的替代口径；此路径**禁用"byte-match"措辞**）|
| **不可回退** | 将来引入整镜像/`.rdata` 字节比对时，只能放弃该比对器 —— 写进风险，而非"永远可回退" |

**「阶段 3 失败」概率实测极低**：`/GR` 不影响 `.text`（79/79 字节相同）⇒ S2/L1 风险 ≈ 0；若移除后变化，应归因于**基线陈旧/棘轮回写**，而非 `/GR`。

---

## 7. 修正后的可执行验收集（核心）

| # | 命令 | 期望 | 阶段 |
|---|---|---|---|
| N1 | `python pipeline/cli.py loop`（同一次内读 stdout）| 记录 S2/L1/errors 三元组 | 0 |
| N2 | flags 一致性断言 | `s4_baseline.flags == 生产 flags` | 0 |
| N3 | C1003 最大行号 | `CCBStage.cpp ≥ 3838` · `free_functions.cpp ≥ 2849` | 0 |
| T3-1 | `family_break_not_at_target` | **109 → 0** | 1 |
| T3-2 | `python3 tests/test_vtable_verify.py` | 61 passed（更新钉值后）| 1 |
| T3-3 | 跨实现一致性 | `bin_table` parity 绿 | 1 |
| T2-1 | `grep -rn "_layout_asserts.h" pipeline/` | **≥ 1**（今天 **0**）| 2 |
| T2-2 | 正相/负相编译 | 正相 rc0；负相 **C2118** | 2 |
| T2-3 | 配对类计数 | `obj_count == raw_bin_count`（今天 **9 类/17 项全 FAIL**）| 2 |
| T4-1 | UI3DCtrl 配对 | `obj 26 → 8`（`0x56ACFC` 连续 8 个代码指针，第 9 个=`0x41400000`）| 2 |
| T1-1 | `/GR` 指纹 | 含 COL 表数 **28/28 → 0/28** | 3 |
| T1-2 | `.text` diff | **identical**（控制实验）| 3 |
| T1-3 | L1 rebaseline 后 | 记录；**不劣于 94 需先证** | 3 |

**不可机械化（需人工裁定的 3 道关口）**：N1/N2/N3 必须先修方案才能机械化。

---

## 8. 本方案的残余不确定（诚实标注）

- **全库覆盖仍是外推**：125/204 TU **今天编译不过** ⇒ 28 张表是 15/204 TU 的样本
- **raw 不可靠**（101/187 表含 ≥3 类族）
- **T1 的收益当前无门禁可度量**（`.rdata` 无比对器）
- **与远端的重复/冲突需要 4 个决策**（§4），未决策前不宜动手
- **门禁接入的 fail-closed 策略未定**