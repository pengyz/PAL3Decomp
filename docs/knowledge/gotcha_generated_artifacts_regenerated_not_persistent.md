---
name: gotcha-generated-artifacts-regenerated-not-persistent
description: 生成产物（decomp JSON / pal3/src/ 生成头 / probe_census.json）是**纯派生物**，任何手改会在下次 export / codegen 被抹掉；要持久必须改"生成源"（annotation 或 IDB），且走 apply → IDB 流入，不直改 IDB 本体
type: gotcha
created: 2026-10-12
updated: 2026-10-12
status: active
sources: [session-2026-10-12, T2/T3/T7 (pal3-converge), docs/knowledge/README.md]
---

# gotcha：改生成产物不持久，改生成源才持久

## 症状（"改对了又回潮"）

- T2 手改 `asm/pal3/decomp/PAL3_SceneUpdateint_int_0044f4c0.json`（把 `name: "PAL3::SceneUpdate"` 改为 `name: "CGameData::SceneUpdate"`）⇒ 端到端验证通过、PAL3 布局从 58/57 恢复到 1/57 ✓
- **下一次 `python pipeline/cli.py loop`（含 export）** ⇒ **decomp JSON 全量重建**（清 OUTPUT_DIR 重导 3649 个）⇒ name 回退 `PAL3::SceneUpdate`、`PAL3.h:113` 的 `virtual int SceneUpdate` 回归、布局可复现回 58/57 ✗

## 为什么

`asm/pal3/decomp/*.json` 是 **`export_full.py` 从 IDB 全量重建的派生物**（`.gitignore` 设计即为此）。
任何对派生物的手改**不进入 IDB**、**不进入 annotation**，下一次导出就被**整体覆盖**。
同理适用于：
- `pal3/src/**`（codegen 从 decomp JSON + annotation 生成）
- `data/status/probe_census.json`（probe 写、compile_regression 读缓存）
- `data/status/s4_baseline.json`（match 写、L1 棘轮回写）

## 正确做法（两条可检查要求）

**① 改"生成源"**（唯一持久面）：
- `data/annotations/structs/*.json` — 走 `apply_annotations.py` → IDB 流入
- `data/annotations/functions.json` / `globals.json` / `enums.json` — 同上
- `asm/pal3/ida_structs.json` — **不要动**（是 export 输出、也是 apply 写入目标，改它等于绕过 annotation）
- **IDB 本体** — 禁止直改（用户硬约束，2026-10-12 T7 明确）；要改 name/type 走 annotation → apply

**② 端到端验证必须跑含 export 的完整 loop**（不是 codegen 单步）：
```
python pipeline/cli.py loop            # apply → export → codegen → probe → match
```
因为只有 export 会触发"派生物全量重建"，只有跑完它才能证明改动持久。

## 反例与正例对照

| 改动 | 面 | 持久？ |
|---|---|---|
| 手改 `asm/pal3/decomp/*.json` 的 name/signature | 派生物 | ❌ 下次 export 被抹 |
| 手改 `pal3/src/GameBase/PAL3.h` 删 virtual | 派生物 | ❌ 下次 codegen 被抹 |
| `data/annotations/structs/CGameData.json` 加 `"owner": "CGameData"` | annotation 源 | ✅ apply→IDB→export 持久 |
| `pipeline/ida/apply_annotations.py` 加 merge 逻辑 | apply 层 | ✅ 持久（但改前须过病灶层检查）|

## 何时使用

- 想"快速改一下让测试过"（对生成产物动手）⇒ **停**，先回答"下一次 export/codegen 会保留它吗"
- 端到端验证只跑了 codegen ⇒ **不够**，必须跑含 export 的 loop
- 归属/名字/签名修完后"看起来对了"⇒ 必须 `python pipeline/cli.py loop` 当场读，不看事后基线

## 关联

- `gotcha_three_competing_baselines.md` — 同族：基线文件不等于实况
- `gotcha_audit_findings_must_be_distilled_into_knowledge.md` — 落盘 ≠ 落对面
- T7 实证（2026-10-12）：owner 字段改 annotation 一处 ⇒ 全量 loop 后 4 项 acceptance 全绿（`CGameData_SceneUpdateint_int_0044f4c0.json` 重命名 · PAL3.h 0 · CGameData.h 1 · audit_type_layout 1/57 · sizeof 4936）
