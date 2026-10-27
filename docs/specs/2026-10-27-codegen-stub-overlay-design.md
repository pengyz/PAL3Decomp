# codegen + stub overlay 设计（manual/ 暂时退役）

> 2026-10-27 · brainstorming 定案。取代「manual/ 平行分叉」迁移路线。

## 0. 决策记录

| 决策 | 内容 |
|---|---|
| D1 路线 | **不维护第二手写分叉**。工作全在 annotation，codegen 输出（pal3/src）是唯一真身 |
| D2 机制 | 「codegen + workaround 补丁」两层 overlay：`phase2/overlay/`（文本补丁，已有）+ `phase2/stubs/`（TU 级 mock，新增） |
| D3 manual/ | **暂时退役**：冻结维护，内容保留为参考素材；不再作为迁移目标 |
| D4 退役判据 | 单元 S2 转 ok ⇒ 删对应 stub。stub 存量是核心进度指标 |

**动机**（2026-10-27 实测）：manual/ fake/error 重构后「92 sources 编译通过」实为 91 个空 TU——验证空气（P1「验证必须作用于被验证物」）；error/ 184K 行真实现无编译路径、头链断裂；平行分叉必然双副本漂移（`docs/knowledge/gotcha_dual_copy_table_divergence.md` 同型教训）。

## 1. 装配契约（第一性基础）

原 PAL3.exe 的**导入表就是装配契约**：gbengine.dll（1021 导出，`gbengine/gbengine.def` 在手）、binkw32、mss32、win32 全部由**真实 DLL** 提供。exe 自身代码 = 唯一重写对象。⇒ 旧 mock/「统一 Mock」概念永久退役；stub 只服务「尚未通过编译的自有代码单元」。

## 2. 目标层级（正交验收）

| 层 | 判据 | 归属 |
|---|---|---|
| L1 忠实性 | match/L1 字节等同（三限定），**度量 codegen 真身** | 管线现状不变 |
| L2 程序完整 | 全符号链接闭合 + 真 exe 可运行 | 本设计的交付 |
| L3 可移植 | platform/linux·android | 后置（manual 退役后另行分叉） |

## 3. 机制设计

### 3.1 两层 overlay（职责分离）

| 层 | 位置 | 语义 | 套用点 | 进 probe 测量？ |
|---|---|---|---|---|
| workaround 补丁 | `phase2/overlay/`（已有，manifest base_sha256 漂移门 + `base/` 基座备份） | 文本级 fix，落进 pal3/src | **按需启用**（2026-10-27 开关翻转）：`codegen --use-overlay` / `loop --use-overlay` / `phase2_retain apply`；`unapply` 还原纯态 | ✓ 但读数**必须带 `overlay.applied/pure` 标签**（probe_census）；**验证/基线锚纯态** |
| **stub 层** | `phase2/stubs/`（新增） | TU 级替换：声明 + 空函数体 | **仅 link-build** | ✗ **永不进入**（probe 只测真身） |

> ⚠️ 铁律：stub 不得写入 pal3/src。否则 S2 量到的是 stub ⇒ 假绿（「92 空 TU」教训重演）。
> `cli.py probe` 语义不变；mock 构建是**另一条命令**（不叫「编译通过」）。
> ⚠️ **补丁态数据漂移**（2026-10-27 实测）：overlay 补丁会让 match/L1/回归对账读数漂移
> （纯态 124/214 被补丁态基线 132/214 误判「回归」）⇒ 默认纯真身，补丁**按需启用**；
> `check` 对 ok（补丁在位）与 pure（纯态）双态 PASS。

### 3.2 stub 形态

- 每个 S2-fail 单元一个 `phase2/stubs/<单元相对路径>_stub.cpp`；
- **include 与真身同款头**（`free_functions.h`/`globals.h`/各类头）⇒ 签名结构性一致，手维护的只有空函数体；
- 函数体空实现（`return 0;` / void 体）；
- **允许手挑真函数原样嵌入**（首个：WinMain 0x00541900，素材取自 codegen 输出及 manual/error 冻结参考件）；
- 初版由 `tools/stub_gen.py` 自动生成（源：codegen 生成头 + decomp JSON 签名），人工修剪。

### 3.3 link-build harness

- 新工具 `tools/mock_link.py`（吸收 manual/pal3/build.py 的 NMake/wine/gbengine.def 链接机制后，manual/ 冻结）；
- 输入：pal3/src 单元清单 + `data/status/probe_census.json`（S2 状态）+ `phase2/stubs/`；
- 分派：S2-ok ⇒ 编真身；S2-fail ⇒ 用 stub（**缺 stub ⇒ fail-loud** 催生成）；
- 链接 gbengine.lib + win32 系 → 可执行产物；
- 产物命名与输出不使用「编译通过」措辞，输出真身覆盖率（见 §4）。

### 3.4 退役棘轮

- 单元 S2 转 ok 但仍留 stub ⇒ 门禁告警（催删 stub）；
- **stub 存量只减不增**：新增 stub 必须带归因（新单元 or 回归）；
- stub manifest 暂不做（v1 靠目录约定 + M3 对账）；若后续需要：记 base_sha256，漂移 = 「基变了，可能已修好 ⇒ 检查退役」。

## 4. 度量（诚实性护栏）

| 指标 | 首读数（2026-10-27 实测） | 方向 |
|---|---|---|
| **真身覆盖率** = 真编单元/总单元 | 124/214 ≈ 58% | 只升 |
| **stub 存量** | 90 | 只降 |
| L1（match，三限定） | 110（棘轮已锚定） | 只升 |
| 链接闭合 | LNK2005=0 / unresolved 台账 | 恶化即归因 |

- 禁止裸用「编译通过 ✓」作为门禁文案；头部指标 = 真身覆盖率 + stub 存量；
- 引用 L1 数字随三限定（`docs/knowledge/gotcha_l1_reloc_dontcare_three_qualifications.md`）。

## 5. manual/ 处置（暂时退役）

- 冻结维护，不删除；`manual/README.md` 顶部加退役标注（状态、日期、去向）；
- `manual/pal3/error/` 184K 行实现 = **stub 嵌入素材库 + 参考**（WinMain/WinProc/Logger 成果不作废）；
- `manual/pal3/build.py` 链接机制移植至 `tools/mock_link.py` 后，manual/ 退出日常流程；
- 未来 L3 可移植分叉若重启，从全量匹配态重新起，不在本设计范围。

## 6. 里程碑

| # | 内容 | 验收 |
|---|---|---|
| M1 | `stub_gen.py` + `mock_link.py` 跑通：90 个 stub 全量生成、链接闭合 | 「空壳但真闭合」：LNK 零错、真身覆盖率 58% 起步 |
| M2 | WinMain 嵌入 free_functions stub（首真函数），free_functions 逐函数渐进嵌入 | WinMain 真身进链；**嵌入 stub 的真函数同样做 L1 字节对拍**（字节来源 = codegen 文本，编译面 = stub TU 内该函数，与原 exe 函数字节比对） |
| M3 | 退役告警接入 `cli.py status`（stub↔S2 对账） | S2 转 ok 留 stub 必报警 |
| M4 | 迭代主循环：annotation fix → S2 转 ok → 删 stub → 覆盖率升（按 FDS 表 N=1 33 个 → N=2 427 个） | 覆盖率单调升、stub 单调降 |
| M5 | stub 清零 ⇒ 全量真身链接 = 真 exe | 真数据运行冒烟 |

## 7. 风险与已知盲区

- **free_functions.cpp 巨型单元**（C1003 截断）：整体退役难 ⇒ stub 内函数级渐进嵌入；评估其进展看截断最大行号（CLAUDE.md 度量盲区条款）；
- **stub 空体运行期假成功**：链接期无害；M5 运行冒烟前 stub 路径的 loud-fail（int3/日志）后置决定；
- **S2 三口径并存**（compile_baseline / baselines/latest / 实况）：本设计只消费 probe_census 单一源，口径随 status 前置预检对齐；
- 新增 stub 单元不进 S2 分母（probe 只测真身），无 new_unit 门禁问题。

## 8. 与现行纪律的衔接

- 病灶层检查 / annotation 证据分级 / 四道门：不变，本设计不触碰 annotation 流程；
- `phase2_retain.py check` 继续管 overlay/；stubs/ 由新对账（M3）管；
- 本设计不含 codegen 内部改动（零管线侵入，与 phase2 钩子同风格）。
