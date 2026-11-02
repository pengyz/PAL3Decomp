# ghidra_track — 双轨验证轨（VERIFICATION-ONLY）

> spec: [2026-11-02-ghidra-dual-track-spec.md](../../docs/specs/2026-11-02-ghidra-dual-track-spec.md)（为什么/判据）
> 实现设计: [2026-11-02-ghidra-dual-track-impl-design.md](../../docs/specs/2026-11-02-ghidra-dual-track-impl-design.md)（架构/ADR/七铁律）
> E2E 规则: [2026-11-02-e2e-fixture-rules.md](../../docs/specs/2026-11-02-e2e-fixture-rules.md)（四钉/错误桶/分层）

**铁律**：VERIFICATION-ONLY · 不准确=不判定 · **零字节轨变更**（不动 `pal3/src` 与 `data/annotations`）· 失败即弃条件门。

---

## 状态板（2026-11-02）

| 件 | 状态 |
|---|---|
| 转换层 `import_annotation.py`（plan IR，5+3 测）| ✅ 可用 |
| 统一生成器 `gen_plan.py`（可重放，_meta v1）| ✅ 可用 |
| 批量写入 `apply_plan.py`（analyzeHeadless postScript 形）| ✅ 可用（D1 三件绿实证）|
| 增量写入 `import_via_daemon.py`（MCP 客户端）| ✅ 可用（会话/工具调用实证）|
| fresh 渲染 `render_fresh.py`（L-fresh 自动化）| ✅ 可用 |
| E2E 判定 `fixture/run_e2e.py`（四钉）| ✅ 可用（case-01: D1 ✅ D3 5/5 ✅ D2=38 基线）|
| 差分器 `diff_tool.py`（三桶+溯源）| ✅ 可用 · **未出首表**（对拍待跑）|
| consume 环（ghidra-reconstruct quick 37 pass）| ⚠ **进行中**：daemon 附着已通，`extractAll` 程序装载断点待破 |
| case-01 黄金夹具（L1 全特性）| ✅ 四钉跑通（D2 烧减待 consume 环）|
| case-02+（L2 边界/L3 对抗）| ⬜ 待立 |

---

## 工作流使用方式

### 0) 前置（一次性）
```bash
# Ghidra 12.1.2（GHIDRA_HOME 钉此版，11.2.1 不可用；安装目录 .gitignore 不入库，需自行解压）
export GHIDRA_HOME=$PWD/tools/ghidra/ghidra_12.1.2_PUBLIC
# submodule + 依赖（已入库）
git submodule update --init
cd thirdparty/ghidra-mcp && npx pnpm@11.0.9 install && npx pnpm@11.0.9 build      # cli dist
cd thirdparty/ghidra-reconstruct && npx pnpm@11.0.9 install && npx pnpm@11.0.9 -r build
# Python 侧: pip install pyghidra
```

### 1) 注解 → plan（纯函数，秒级）
```bash
python3 ghidra_track/gen_plan.py <ann_dir> out/plan.json
# ann_dir 布局 = data/annotations 同形：functions.json / structs/*.json（methods 自动并入）/ globals.json
```

### 2) plan → Ghidra 库（批量写入，首灌/重建）
```bash
# 重建 = 清 .gpr + .rep 整目录再导（L-rebuild，禁修补旧库）
$GHIDRA_HOME/support/analyzeHeadless ghidra_track/ghidra_proj <PROJ> -import <binary> \
  -scriptPath ghidra_track -postScript apply_plan.py out/plan.json
# 幂等（deleteAll 重灌）· sizeof 对账 · apply_report.json 机读
```
⚠ 生命周期铁律：**pyghidra 只准只读探针**（写入走 postScript/daemon——readOnly 布尔与 FS 提交双坑已实证）；
daemon 与 headless **互斥持库**（跑前清会话/锁，L-lock）。

### 3) 库 → 丑C（consume 环，37 pass quick）
```bash
cd thirdparty/ghidra-mcp && GHIDRA_HOME=... nohup node packages/cli/dist/bin.js &   # daemon
# 产品通道建会话：create_session{binaryPath: <proj>.gpr, programPath: <prog>}
cd thirdparty/ghidra-reconstruct
GHIDRA_PROJECT_DIR=$PWD/../../ghidra_track/config \
GHIDRA_PROJECT_PATH=ghidra://localhost:8432/<PROJ> \
GHIDRA_PROGRAM_PATH=<prog> GHIDRA_MCP_TOKEN=local-dev \
npx tsx run.ts          # 默认 preset=quick（--transform-preset full 可选）
```

### 4) 丑C → 编译判定（四钉）
```bash
python3 ghidra_track/fixture/run_e2e.py <case-id>
# D1 布局/sizeof/持久化 · D2 编译错误四桶 · D3 渲染语义（fresh-session）· D4 对拍
# 报告: fixture/cases/<case-id>/report.json
```

### 5) A/B 对拍差分（M1 判据）
```bash
python3 ghidra_track/diff_tool.py a_errors.txt b_errors.txt data/status/dual_track_m1_diff.json --slice <name>
# 三桶: A_only=Hex-Rays 约束候选 / B_only=伪影桶 / intersection=共性（逐条 trace+class 待裁）
```

### 新增 E2E 用例（迭代开发回归）
```
ghidra_track/fixture/cases/<case-id>/{src,annotations,expected,case.json}
# 规则 = e2e-fixture-rules.md：期望即真值 · 一案一目录 · 新特性 = 新 case（禁改期望迁就实现）
```

---

## 目录

```
import_annotation.py   转换层（纯函数，载体无关）
gen_plan.py            统一 plan 生成器（可重放，_meta v1）
apply_plan.py          批量写入（analyzeHeadless postScript 形）
import_via_daemon.py   增量写入（ghidra-mcp MCP 客户端）
render_fresh.py        fresh-session 渲染器（L-fresh 自动化）
diff_tool.py           A/B 三桶差分器（M1 判据件）
config/project.json    reconstruct 项目配置
fixture/               E2E 体系（cases/ + run_e2e.py + gen_types.py）
out/                   派生区（gitignore，可弃）
ghidra_proj/           Ghidra 项目（gitignore，可整删重建）
thirdparty/            ghidra-reconstruct + ghidra-mcp（git submodule）
```

## 经验约束（七铁律摘要，全案见实现设计 §4.5）
L-persist（写入走完整进程收尾）· L-lock（daemon↔headless 互斥）· L-fresh（渲染判据只认 fresh-session）·
L-rebuild（库坏=整删重建）· L-addr（fixture 一律 -no-pie + nm 真址）· L-assert（patch 必锚点校验）·
L-no-self-kill（进程清理 python 排己法）
