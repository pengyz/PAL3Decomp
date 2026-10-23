# Step 0 完备性复核

（对抗复核·路 1；只读复核，未改任何产品文件。依据 `docs/specs/step0_zero_risk.md` + 实测核对）

## 完备性

3 动作方向对，但有实质缺口：

1. **② 白名单与实况脱节（最严重）**。spec 列 11 条却称"8 处"；逐条实测：`emit_headers.py:781` 是 `_annview` 读点 import 本身、`:4322` 是 `data.values()`、`stage3_cleanup.py:177` 空行、`ast_transform.py:337` 是修复注释、`transform.py:67` 实际在 `pipeline/gen/stages/transform.py`（读 `functions.json`）。而真直读 `scoped_targets.py:27`、`emit_headers.py:563/1427/4350`、`stage4_substitution.py:2513/2552/2585` 未列入。⇒ 动手前缺一步"**违规清单校准**"；且 CLAUDE.md"尚有 3 处"（emit_headers:3259 等）实测均已收敛到 `_annview`——三方口径互斥，先归一清单再谈扩闸。
2. **① 缺 diff 归一化定义**。IDA `data_members` 与注解 `known_members` 语义不对称（dict-union / inline union / overlap 位面复用），直接 diff 必误报；不定义匹配算法，报表是噪声。
3. **缺 DoD 与 P1-5 定义**。"P1-5 验证（同树 A/B）"只出现在 checkbox，3 个动作都没给命令与判据；Step 0 何时算完成无退出标准。
4. **漏第 4 份基线** `link_census.json`（link_probe 棘轮），"3 基线"提法不全。

## 可行性

1-2 天**仅在削减③后成立**：① 约 0.5 天（v1 报表）；② 约 0.5 天；③ 若按"统一数字"做，需逐基线裁决+验证不掩盖退化，实为 1-2 天。且**行号白名单已被证伪**（行号必然漂移，上线即失真），须改 AST/文件+函数锚定，成本+0.5 天。合计紧但可行。

## 挑刺

1. **③ 定性错误，且是方案最大风险**。三份基线并非"互斥"：`compile_baseline`=ok/fail 快照（S2 120/**214**）、`latest.json`=(code,msg) 多重集对账（140/**205**）、`s4_baseline`=L1 棘轮（**194**）。分母不同=三个不同裁判，不是未校准。`align_baselines.py`"统一数字"=**无理由静默回写棘轮基线**，正犯 CLAUDE.md 反复警告的病（L1 棘轮只能 `match --rebaseline "<理由>"` 显式推进；事后查基线判退化不可靠）⇒ 会**掩盖真退化**，风险≠0。
   **更好方案**：③ 改"**口径对齐=测量时机归一**"——一律在同一次 `loop` 运行中当场读输出（CLAUDE.md 强制规则），`status --strict` 已能判基线不一致并 exit 1，只读对照即可，**不写任何基线**。
2. ② 白名单按锚定重做；扫 `pipeline/gen/**/*.py`（非 `*.py` 平铺）；断言须带判别力变异验证（仓内已有 M2/M3 反例纪律）。
3. ① 输出应同时给"**消费者读哪个源**"映射（服务阶段 2 MERGE 策略），否则只列差异不指方向。

## verdict

**有条件通过**。① 保留；② 白名单先校准+改锚定；③ **删"统一数字"，改只读口径对照（禁写基线）**。改后 1-2 天成立；按原案执行有掩盖退化的实风险，"风险 0"不成立。
