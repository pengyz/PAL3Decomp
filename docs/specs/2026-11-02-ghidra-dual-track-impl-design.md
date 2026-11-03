# ghidra 双轨验证轨·实现设计（完备性方案）

> 2026-11-02 · 分支 feature/ghidra-dual-track · 状态：设计定稿
> 与 spec 的分工：`2026-11-02-ghidra-dual-track-spec.md` = 为什么做/判据（G1-G4/M1-M4 验收）；
> **本文 = 怎么做/架构**，是后续迭代开发的实施基准。此前旁路试错的全部结论在此固化为设计约束。

---

## 1. 目标与非目标

### 目标
1. **annotation 单源双渲染**：同一份注解 JSON，经两条独立渲染轨产出可比对的 C：
   - A 轨（字节轨）：IDA/Hex-Rays → codegen → pal3/src（既有管线，本设计**零字节轨变更**）
   - B 轨（验证轨）：Ghidra → ghidra-reconstruct → 丑C（VERIFICATION-ONLY，可弃件）
2. **差分语料生产**：B−A 编译错误差分 ⇒ Hex-Rays 约束隔离清单（transform-broken 桶=约束证据）
3. **E2E 夹具体系**：已知真值的独立集成测试（case 体系），支撑转换层/管线的迭代开发回归
4. **可迭代性**：每层可独立测试、独立替换、独立重跑；判据自动出数（report.json）

### 非目标
- 不追求 B 轨产物的可读性/交付价值（quick 预设=可编译铁律档）
- 不替代 A 轨的字节匹配职责（L1 三限定口径不变）
- 不做 cpp-parser 上字节轨（2b 暂缓，三险见 spec）
- 本轨产出不回写 data/annotations（注解是源不是汇）

---

## 2. 总体架构

```
┌─ annotation JSON（单一数据标准：structs/functions/globals，正式 schema）─┐
│                                                                        │
│   ①转换层 build_import_plan()  [纯函数 · 离线可测 · 载体无关]            │
│        ↓ plan.json（声明式 IR：set_name / define_struct / define_union  │
│                     / set_func_sig / define_global）                    │
├────────────────────────┬───────────────────────────────────────────────┤
│ ②写入面（双通道）        │ ③Ghidra 库（gpr 项目 · 唯一持久事实）          │
│   · 批量通道：analyze-  │                                               │
│     Headless postScript │   ④消费面：ghidra-mcp daemon                  │
│     (apply_plan.py)     │      → ghidra-reconstruct [quick|full]        │
│     = 首灌/重建用        │      → 37 AST pass → 丑C out/                  │
│   · 增量通道：daemon     │                                               │
│     set_prototype/…     │   ⑤判定面：run_e2e 四钉                        │
│     = 迭代微调用         │      D1 布局/sizeof/持久化                     │
├────────────────────────┤      D2 编译错误桶白名单                        │
│ A 轨（既有 IDA 管线）    │      D3 渲染语义钉（fresh-session）            │
│   apply→IDB→codegen     │      D4 双轨对拍（同 plan 差分）               │
└────────────────────────┴───────────────────────────────────────────────┘
```

**数据所有权**：annotation=源；plan=派生（可重放）；Ghidra 库=派生（可从 plan 重建）；丑C=派生（可弃）；
report.json=度量产物（入库）。

---

## 3. 核心设计决策（ADR）

| # | 决策 | 理由（含实证） |
|---|---|---|
| ADR-1 | **plan IR 载体无关** | 同一 IR 双渲染=D4 对拍公平性前提；转换逻辑离线 TDD（5 测）；排障时「语义错 or API 错」一翻两瞪 |
| ADR-2 | **写入面走 Ghidra 完整进程生命周期**（postScript / daemon worker），**禁止 pyghidra 旁路直写**为产品通道 | pyghidra 旁路两真 bug 实证：①`openProgram` 第三参=readOnly（脱钩副本=持久化死幻象）②JPype 拆 JVM 跳 FS 收尾提交（`~index.dat` 永驻=隔进程看空项目）。**旁路只许做只读探针**（探库态），写入一律走有完整收尾的通道 |
| ADR-3 | **签名面用 ghidra-mcp `set_prototype`**，不自造 | 其 worker 已解 thiscall/约定归一（`DataTypeOps` 归一化表 `_thiscall→__thiscall` 等）+ `set_custom_signature`（IDA `__usercall` 面）；D2 千级 thiscall 实战验证 |
| ADR-4 | **fixture 黄金夹具 + 四钉判定**为唯一验收口径 | 受控真值=管线问题与可编译性零混淆（已实证：union 映射缺口/PIE 轴/幻象持久全自动归因到桶） |
| ADR-5 | **渲染判据只认 fresh-session**（T3 钉） | 实证：apply 同会话 emit=缓存陈旧渲染（假阴）；落盘→重开→再渲染=真实能力 |
| ADR-6 | Grep/patch 工程纪律：**改文件必 assert 锚点** | 实证：空打补丁 4+ 次（无 assert 的 str.replace 静默 no-op） |

---

## 4. 组件详设

### 4.1 转换层 `ghidra_track/import_annotation.py`（已有，增量演进）
- `build_import_plan(functions, structs, globals) -> [op]`：纯函数。语义：
  - 已 mangled 名（`?` 开头）直通禁重绞；零参 `XZ` 形
  - 载体诚实化 `honest_signature`：`__fastcall(int self)` → thiscall 本体（self 消隐）
  - inline-union dict 型 → `define_union` op（禁字节桩）；嵌套内联 struct 同理（M2 补）
  - dict 键偏移形（known_members offset 在键）
- 测试锚：`tests/test_annotation_import.py`（5 测）+ `test_apply_plan_logic.py`（3 测）
- **演进规则**：新增注解语义（位域/枚举/模板实例）必须先落 TDD 用例再落实现

### 4.2 写入面（双通道，各司其职）

**批量通道** `ghidra_track/apply_plan.py`（首灌/重建）：
- 运行形：`analyzeHeadless <projdir> <projname> -import <bin> -scriptPath ghidra_track -postScript apply_plan.py <plan.json>`（**postScript 形=退出自带 FS 提交**，ADR-2）
- 职责：结构两遍建（类型依赖解）/union 建型/`replaceAtOffset` 覆盖式成员命名/签名（经 4.3 的代理或本地 ArrayList 形）/sizeof 对账/机读 `apply_report.json`
- 幂等：重建=清 `.gpr`+`.rep` 整目录重导（不修补旧库）；单库内重放=deleteAll+重灌

**增量通道**（ghidra-mcp daemon 工具，M2 起）：
- `create_structure/create_union/create_label/set_prototype`（+`apply_changeset` 批量，expect 乐观锁）
- 用途：迭代开发期的微调（改一个签名/加一个成员）不走全量重建
- 客户端：`ghidra_track/import_via_daemon.py`（MCP Streamable HTTP，已有骨架）

### 4.3 消费面（ghidra-reconstruct 集成）
- 前置：daemon 持库会话（`create_session{binaryPath: <gpr>, programPath: <name>}`）
- 运行：`npx tsx run.ts`，env `GHIDRA_PROJECT_PATH=ghidra://localhost:8432/<proj>`
- 预设：`quick`=仅伪影清除（D2 变换效果灯基线）；`full`=全 pass（对照）
- 产物：`ghidra_track/out/<case>/reconstruct/` 丑C + `.cpp.map`
- 快照：`.ghidra-mcp/codegen-snapshot`（断点续跑，168h 时效）

### 4.4 E2E 判定面 `ghidra_track/fixture/run_e2e.py`（规则= `2026-11-02-e2e-fixture-rules.md`）
- 四钉：D1（机测 layout 对账 + 库内 sizeof + **持久化断言**）/ D2（错误四桶白名单）/ D3（渲染语义钉·fresh-session）/ D4（双轨对拍）
- 每 case 产 `report.json`；全绿判据=四钉全过
- 演进规则：新特性=新 case 目录（期望即真值，禁改期望迁就实现）

### 4.6 差分器 `ghidra_track/diff_tool.py`（spec M1 判据件）
- 输入：`a_errors.txt`（A 轨=Hex-Rays/codegen 编译错误）+ `b_errors.txt`（B 轨=丑C 编译错误），行形 `unit: error: TEXT`
- 归一：地址/数字/空白 → `error_key`（对齐键）；按 key 聚合计数
- 输出 `data/status/dual_track_m1_diff.json`（schema_version:1）：三桶
  - `A_only`=仅 A 有 ⇒ **Hex-Rays 约束候选**（spec M1「仅 A 有」簇归因对象，逐条 trace+class 裁定）
  - `B_only`=仅 B 有 ⇒ 验证轨伪影/转换层桶
  - `intersection`=共有 ⇒ 注解/共性问题
- 每 item 带 `text/source_unit/count/class/trace`（class 归因**留空待逐条裁定**——不准确=不判定）
- 定性基准（与 e2e-rules §3 对齐）：B 侧 `transform-broken`=变换应消（quick/full 的效果面）；
  差分后 A_only 里**归因为 Hex-Rays 约束**的条目=约束隔离清单产出

### 4.5a 真值轴纪律（自洽 ≠ 对真，2026-11-03 立）

| 轴 | 证明 | 裁判 |
|---|---|---|
| **自洽轴** | 注解内部无矛盾/可编译/类型闭合（灌注成功、sizeof 对账、布局网、编译门）| B 面规则校验 |
| **对真轴** | 布局/签名/归属与**原二进制功能等价** | **L2 obj 对拍（oracle 语义掩码）→ L3 字节匹配**；逐条变更的 **A 级证据**（reg+disp32/绝对址）为质押物 |

**铁律**：偏移全错的布局同样全绿（自洽轴无法区分）⇒ 任何「修复完成」声明必须携对真证据；
findings/审计清单=**线索非定论**；终判唯一=L3 字节匹配。B 面价值=**识别**（知道查哪），修复正确性由对拍层+证据纪律保证。

### 4.5 生命周期与状态管理（铁律，全部来自实证）

| 铁律 | 出处实证 |
|---|---|
| **L-persist**：写入必须经完整进程收尾（postScript/daemon worker）；pyghidra 只读探针 | `~index.dat` 永驻案 |
| **L-lock**：daemon 与 headless/pyghidra **互斥持库**（`.gpr.lock`）；跑管线前清会话 | daemon 锁撞 apply 案 |
| **L-fresh**：渲染判据只认 fresh-session 读数 | emit 缓存假阴案 |
| **L-rebuild**：库损坏/换 bin = 清 `.gpr`+`.rep` 全重建，禁修补 | 半提交孤儿 `.rep` 案（断导残件） |
| **L-addr**：fixture 一律 `-no-pie` 编译+nm 真址入注解；**run_e2e 编译步钉死 -no-pie** | PIE 覆盖回退案 |
| **L-assert**：文件 patch 必带锚点 assert+语法校验 | 空打补丁 4 案 |
| **L-no-self-kill**：进程清理用 python 排己法，禁裸 `pgrep -f` | 自杀坑 2 案 |

---

## 5. 目录与数据布局

```
ghidra_track/
  import_annotation.py      转换层（纯函数）
  apply_plan.py             批量写入（analyzeHeadless postScript 形）
  import_via_daemon.py      增量写入（MCP 客户端）
  config/project.json       reconstruct 项目配置
  fixture/
    cases/<case-id>/{src,annotations,expected,case.json,report.json}
    run_e2e.py              四钉判定
    gen_types.py            case 注解→types.h
  out/                      派生区（.gitignore）：plan/<case>_plan.json · slice/ · reconstruct/
  ghidra_proj/              派生区（.gitignore）：Ghidra 项目（可整删重建）
docs/specs/2026-11-02-{ghidra-dual-track-spec,e2e-fixture-rules,ghidra-dual-track-impl-design}.md
data/status/review_persist_arch_20261102.md   对抗复核定谳（C 案）
thirdparty/{ghidra-reconstruct,ghidra-mcp}    submodule（pin 版本）
tools/ghidra/ghidra_12.1.2_PUBLIC             Ghidra（GHIDRA_HOME 钉 12.1.2）
```

---

## 6. 实施计划（迭代支撑）

| 里程碑 | 内容 | 验收（沿用 spec M1-M4 口径） |
|---|---|---|
| **M1 收官**（当前） | ①case-01 四钉全绿（✅ 已达：D1 三件+D3 5/5）②**PAL3 切片双轨差分**（spec:102-104 口径）：A 轨=既有 probe/match 错误面，B 轨=切片灌库→reconstruct quick→编译 ③diff_tool 产三桶清单**逐条溯源归因** ④D2 变换红绿对照（transform-broken 烧减率）| **spec:86 口径**：`dual_track_m1_diff.json` 三桶差分清单+「仅 A 有」簇≥1 条 Hex-Rays 约束归因（带 trace） |
| **M2 全量** | PAL3 全量注解灌库（~2000 函数/3935 认领）→ reconstruct quick 全量丑C → 编译 → 错误四桶分账 → B−A 差分=Hex-Rays 约束清单 | 全量差分表+桶账 |
| **M3 边界登记册** | spec G3：边界语义差登记（引用/模板/内联汇编…） | 登记册 v1 |
| **M4 条件门** | 2a 借壳（Python 变换插件化+tiering）评估 | 条件门判定文 |
| **持续** | 新 case 爬层（L2 边界：函数指针/位域/虚继承/静态成员；L3 对抗：-O2/内联/switch） | 每 case 四钉绿入 CI 快照 |

**迭代开发支撑形态**：
- 改注解 → plan 重放（秒级）→ 四钉回归 = 单轮闭环
- 增量微调走 daemon 通道（不重建）
- 大改/换 bin 走 L-rebuild 全重建
- 每轮 report.json 落盘=趋势可查

---

## 7. 风险 / 止损 / 降级

| 风险 | 止损判据 | 降级（spec §5） |
|---|---|---|
| daemon 通道对本地 .gpr 的程序装载语义未通 | 1 天内未出有效读数 | 消费面暂用 analyzeHeadless `-postScript` 内嵌 reconstruct 抽取等价物 / 单函数对偶旁证 |
| reconstruct quick 对 MSVC 系 32 位伪影覆盖不足 | D2 transform-broken 不降 | 清单化「伪影保留档」=本身就是约束语料（失败即弃条款复评） |
| fresh-session 渲染与期望不一致 | 系统性不一致 | 渲染判据只认 fresh 侧（ADR-5 已含） |
| 任何推进需动字节轨 | — | **立即停**（spec 铁律 3） |

---

## 8. 验收判据（M1 终口径）

1. `case-01 report.json`：D1 三件（layout/sizeof/persistence）PASS · D2 ⊆ 白名单 · D3 5/5（member-access/union-view/overload-split/zero-arg-xz/vtable-call，fresh-session）· D4 挂位或出首表
2. `data/status/dual_track_m1_diff.json`（diff_tool 产，schema_version:1）：A_only/B_only/intersection 三桶清单**逐条 trace+class**；「A_only」中≥1 条 class=hexrays-constraint（Hex-Rays 约束归因）
3. `git diff` 对 `pal3/src` 与 `data/annotations` **零字节变更**
4. 生命周期铁律 L-persist/L-lock/L-fresh 在 run_e2e 内自动执行（不靠人记）

---

## 9. 附录：已定谳问题→设计约束对照

| 问题（这两天实证） | 定谳 | 转入约束 |
|---|---|---|
| 持久化死（ReadOnlyException） | `openProgram` 第三参=readOnly 传错 | ADR-2 / L-persist |
| 隔进程看空项目（Program not loaded） | pyghidra 退出不提交 FS（`~index.dat`） | ADR-2 / L-persist / L-rebuild |
| varargs `replaceParameters(*pd)` 静默错绑 | JPype varargs 坑 | 4.2 ArrayList 形 / ADR-3（首选 set_prototype）|
| `setThis` 不存在（except 吞错） | API 面臆测 | L-assert 同族：API 先反射后调用 |
| PIE 地址轴错位 | run_e2e 编译步覆盖 no-pie | L-addr |
| 空打补丁（4+ 次） | str.replace 无 assert | L-assert |
| emit 缓存假阴 | 同会话 decompile 陈旧 | L-fresh |
| daemon 项目锁互撞 | 双进程持库 | L-lock |
| pgrep 自杀（2 次） | 正则自匹配 | L-no-self-kill |
