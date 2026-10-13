# T41 迭代台账（2026-10-13 · pal3-converge · 迭代 8 收口）

> **命名注**：`_t6_`（迭代 1）· `_t36_`（迭代 6）· `_t38_`（迭代 7）已使用，本迭代 8 收口用 `_t41_iteration_ledger.md`（按复核 task id 命名）避免冲突。

**会话**：pal3-converge · **成员**：diagnoser（T42 收口，T6/T16/T25/T29/T33/T36/T39 等价）
**覆盖**：T40 实施 → T41 复核（t41 pass 无需 repair）
**收口态基线**：S2 **127/209** · 总错误 **1337** · L1 **132** · matched **777/952** · partial 553 · L1 率 **132/685 = 19.3%**（仍在 18-19.5% 平台内）

---

## 一、本迭代裁决（Decisions）

### D1 · T40 T38 F1/F2/F3 收口（R15 单测落盘 + 措辞限缩 + 基类回落递归化）
- **背景**：T38 复核发现三项非阻塞（F1 单测无存世工件 · F2 措辞强于实证 · F3 基类回落单层）
- **裁决**：**三项一次收口**（R15 单测落盘 + 措辞限缩 + 递归化）
- **F1（R15）**：`tests/test_stage4_ptr2ulong.py` 落盘 —— 7 测全过（3 目标形 + 2 非目标 + 幂等 + 递归回落）
  - `python -m pytest tests/test_stage4_ptr2ulong.py -v` **精确命令 7 passed** ✓
  - `tests/pytest.ini addopts=--assert=plain` 绕过环境 pytest 的 assert-rewrite AST 不兼容（`TypeError: required field "lineno" missing from alias` 实测）
- **F2（措辞限缩）**：stage4 [T37] 注释改为「**类型级字节等价**（x86-32 位拷贝成立），**非端到端 L1 实证**」
- **F3（递归化）**：`_lookup_member_with_bases` BFS 沿 `struct_bases` **递归上溯**（替换两处单层回落）
- **效果**：总错误 **1339→1337（−2**：递归回落消 2 行孙基类成员解析行）· S2 **127/209** 稳定 · **L1 132→132 不回退** · **零翻红**

### D2 · T41 三项独立复验 + 产物深度 2 双证 + −2 逐字归因（pass 无需 repair）
- **T41 复核**：T40 的声称（S2 稳定 · L1 不回退 · 总错误 −2）**当场读实测成立**
- **三项独立复验**：F1 单测工件可复现（精确命令 7 passed）· F2 措辞限缩如实 · F3 递归化生效
- **产物深度 2 双证**：`CCBRoleState`→`SceneObj`→`UIWnd` 深度 2 链产物实证
- **−2 逐字归因**：递归回落消 2 行孙基类成员解析行

### D3 · T41 的 1 项 low 非阻塞发现
- **`test_base_fallback_recursive` 未针住递归**：
  - 数据路仅 depth 1（`UIAnimateCtrl`→`UIWnd` 直基）
  - 断言式 `assertTrue(t and '*' in t or t)` **因优先级过松**（`or t` 让 `t` 非空即过）⇒ 未真正针住递归
  - **建议**：换成产物实证的 **depth-2 链**（`CCBRoleState`→`SceneObj`→`UIWnd`）并收紧 `assertIn('*', t)`

---

## 二、本迭代教训（Lessons）

### L1 · R15 单测落盘（T38-F1 → T40）
- **症状**：T37 声称「单测四形」但 `tests/` 无存世工件
- **T40 修**：`tests/test_stage4_ptr2ulong.py` 落盘（7 测）
- **规则**：**改工具必须跑其测试**（R15），且**测试必须落盘**（不能只在 commit message 里声称）

### L2 · pytest 环境坑（T40 附带发现）
- **症状**：环境 pytest 的 assert-rewrite AST 不兼容（`TypeError: required field "lineno" missing from alias`）
- **修**：`tests/pytest.ini addopts=--assert=plain` 绕过；unittest 直跑亦 7/7 ✓
- **规则**：**pytest 环境坑须沉淀**（`docs/knowledge/` 已记 `8f6400e84`）

### L3 · 递归上溯双证（T40 F3 + T41）
- **T40**：`_lookup_member_with_bases` BFS 递归上溯（替换单层回落）
- **T41**：产物深度 2 双证（`CCBRoleState`→`SceneObj`→`UIWnd`）
- **规则**：**递归修复必须配深度 ≥2 的双证**（单层测不出递归是否生效）

### L4 · 断言式优先级过松（T41 low）
- **症状**：`assertTrue(t and '*' in t or t)` —— `or t` 让 `t` 非空即过
- **规则**：**断言必须收紧**（`assertIn('*', t)` 或 `assertTrue(t and '*' in t)`），不能用 `or` 让弱条件通过

---

## 三、T41 的 1 项 low 非阻塞发现

| 编号 | 内容 | 处置 |
|---|---|---|
| **low** | `test_base_fallback_recursive` 未针住递归（数据路 depth 1 + 断言式优先级过松）| **挂账**（下轮换成 depth-2 链 + `assertIn`）|

---

## 四、挂账交接（下轮）

| 项 | 归属 | 备注 |
|---|---|---|
| **T41 low** | tests | `test_base_fallback_recursive` 收紧（depth-2 链 + `assertIn`）|
| **T35-F1 requiredFix** | 独立轮 | 补 T30 预测 3 单元名单 |
| **T35-F2** | 独立轮 | 簇枚举口径精确命令 |
| **T34 挂账** | annotation/codegen | 真 lvar / 字符串全局 / E.T 形 |
| **T32-F1/F2** | 独立轮 | E3 量化口径 · 漂移清单 |
| **T22-F3** | 独立轮 | 三形守卫清点 647 行 |
| **T17/T19/T28** | 多层 | 归属批 · adjudicate_lvar_type · O1/O2 |

---

## 五、迭代 8 效果对照（判据 v2.1 `aeb0adf41`）

| 指标 | 迭代 7 收口 | 迭代 8 收口 | Δ | 判据 |
|---|---|---|---|---|
| **L1 绝对数** ⭐ | 132 | **132** | **0**（不回退 ✓）| ✅ **主判据不回退** |
| **S2 绿单元** | 127/209 | **127/209** | **0** | ✅ |
| **总错误** | 1339 | **1337** | **−2** | ✅ |
| **matched** | 777/952 | **777/952** | 0 | — |
| **partial** | 553 | 553 | 0 | — |
| **L1 率**（参考）| 19.3% | **19.3%** | 0pp | ⚠️ 分母失真 |

**L1 率说明**：
- L1 绝对数 **132→132 不回退** ✓（主判据）
- **S2 绿 +0**（本迭代是收口批，非修复批）
- **L1 率 19.3% 仍在 18-19.5% 平台内**

**迭代 8 里程碑**：
- **L1 保持 132**（不回退 ✓）
- **总错误 −2**（1339→1337，递归回落消孙基类成员解析行）
- **T38 F1/F2/F3 全部收口**（R15 单测落盘 · 措辞限缩 · 递归化）

---

## 六、验证证据（本 T42 收口）

| 项 | 命令 | 结果 |
|---|---|---|
| 全量 loop 端到端（含 export）| `python pipeline/cli.py loop --expect-s2 127/209 --expect-errors 1337 --expect-l1 132` | **apply 0/13.6s · export 0/182.9s · codegen 0/223.2s · probe 0/74.2s · match 0/310.8s**（**全 rc=0**）· **✓ 基线断言全部满足** |
| 三基线刷新 | `regression_detector.py --save-baseline` + `compile_regression.py --update-baseline` + match 自动 | `baselines/20261013_112010.json`（209 文件 127 ok 82 fail）· `compile_baseline.json` 已更新 · `s4_baseline.json` stats: symbols=952 matched=777 L1=132 partial=553 |
| L1 当场读 | `python pipeline/cli.py match` | `matched 777/952 · L1 132 · partial 553 · L1 rate 132/685 = 19.3%` · `[L1 ratchet] previous 132 -> current 132` ✓ |
| CLAUDE.md:150 参数 | 编辑 | `--expect-s2 127/209 --expect-errors 1337 --expect-l1 132`（从 `127/209 · 1339 · 132`）|
| 当场读数（非事后基线）| `probe_census.json generated_at=2026-10-13T11:13:36` | S2 127/209 · 总错误 1337 |

**Confidence: high**（**连续四次全量 loop 全 rc=0**（T33/T36/T39/T42）+ 基线断言全部满足 + R15 单测工件精确命令可复现 + 产物深度 2 双证 + −2 逐字归因）

---

## 七、迭代 8 完成度总结

**T40→T41 两任务全部完成**：
- **T40**：T38 F1/F2/F3 收口（R15 单测落盘 + 措辞限缩 + 基类回落递归化）
- **T41**：pass 无需 repair（三项独立复验 + 产物深度 2 双证 + −2 逐字归因 + 1 项 low 非阻塞）

**累计效果**：**L1 保持 132**（不回退 ✓）· **总错误 −2**（1339→1337）· **T38 F1/F2/F3 全部收口**

**下轮入口**：按挂账 7 项推进（T41 low test_base_fallback_recursive 收紧 · T35-F1 requiredFix · T35-F2 簇枚举口径 · T34 挂账 · T32-F1/F2 · T22-F3 · T17/T19/T28）
