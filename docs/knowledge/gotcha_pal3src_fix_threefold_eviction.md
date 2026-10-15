# pal3/src 手改三重灭失（Phase 2 fix 零留存根因）——已机制化为 phase2/overlay

**现象**：Phase 2 手工 fix 直接改 `pal3/src/**` 必然丢失：单测/字节比对当场有效，
下一轮 codegen 即"回潮"，且 git 里**没有任何痕迹**（此前多轮会话反复踩）。

**为什么（三重灭失，verifier 2026-10-15 复核实录）**：
1. **射程生成逐文件覆盖**——`pipeline/gen/stages/emit_cpp.py` 对每个 .cpp
   `open(out_path, 'w')` ⇒ 只跑 `codegen cpp` 也会覆盖手改；
2. **`codegen all` rmtree 全树**——`pipeline/gen/codegen.py:cmd_clean` 整删重建；
3. **git 不跟踪**——`.gitignore:130` 目录级排除 `pal3/src/`（re-include 不可行，
   尝试过）⇒ 手改连 diff 都留不下。

**机制（方案 A'，已实施）**：`tools/phase2_retain.py` + `phase2/`（tracked）：
- `phase2/manifest.json` 条目（mode=override|pin · base_sha256 · new_unit）
- `phase2/overlay/<相对路径>` fix 副本（git 托管 = 独立基线）
- `phase2/base_census.json` 派生物（gitignore）
- 钩子：`codegen.py` headers/cpp/all 三分支末尾 `retain apply`（manifest 空=no-op；
  `--no-retain` 逃生阀；override 漂移 **exit 2 fail-loud**，pin 跳过+告警）
- 自校验：`phase2_retain.py check` 逐条目 sha256(pal3/src)==sha256(overlay)

**何时使用**：任何"改 pal3/src 让字节更近"的 Phase 2 fix ⇒ **先 `adopt` 收编基底 →
改 overlay 副本 → `apply`**，禁止直改 pal3/src。codegen 输出变了（漂移门报警）⇒
人工复核 overlay 是否仍适用 → `rebase` 刷新 base。新增 .cpp 单元必须 `new_unit: true`
（改 S2 分母 209 ⇒ 必须同步刷新门禁数字）。
